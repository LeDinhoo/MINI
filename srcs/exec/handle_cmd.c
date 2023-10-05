/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:30:51 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/03 14:24:50 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->cmd = NULL;
	node->cmd_path = NULL;
	node->cmd_args = NULL;
	node->is_last = 0;
	node->redir.output_file = NULL;
	node->redir.append_file = NULL;
	node->redir.input_file = NULL;
	node->redir.heredoc_content = NULL;
	node->next = NULL;
	return (node);
}

// Fonction pour gérer une commande
void	handle_arg(t_cmd *cmd, const char *argument)
{
	int	num_args;

	num_args = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[num_args] != NULL)
			num_args++;
	}
	cmd->cmd_args = realloc(cmd->cmd_args, (num_args + 2) * sizeof(char *));
	if (cmd->cmd_args == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	cmd->cmd_args[num_args] = strdup(argument);
	cmd->cmd_args[num_args + 1] = NULL;
}

void	handle_cmd(t_token *start, t_cmd *node)
{
	if (!node || !start)
		return ;
	node->cmd = ft_strdup(start->str);
	handle_arg(node, start->str);
	return ;
}

void	setup_command(t_mini *mini, t_token *current, t_cmd *current_cmd,
		t_expect *ex)
{
	if (current->type == CMD)
	{
		if (handle_redirection(current_cmd, current, ex) == 0)
		{
			handle_path(mini->path, current_cmd, current->str);
			handle_cmd(current, current_cmd);
		}
	}
	else if (current->type == ARG)
	{
		if (handle_redirection(current_cmd, current, ex) == 0)
			handle_arg(current_cmd, current->str);
	}
}

void	cmd_args(t_mini *mini)
{
	int				new_cmd;
	struct s_expect	ex;
	t_token			*current;
	t_cmd			*current_cmd;

	current = mini->start;
	current_cmd = NULL;
	new_cmd = 0;
	init_expect(&ex);
	while (current != NULL)
	{
		if (new_cmd == 0)
		{
			current_cmd = create_new_cmd();
			new_cmd = 1;
		}
		setup_command(mini, current, current_cmd, &ex);
		find_redirection(current, &ex);
		if (current != NULL && (current->next == NULL || current->type == PIPE))
		{
			add_cmd_node(current_cmd, &mini->cmd_tab);
			new_cmd = 0;
		}
		current = current->next;
	}
}
