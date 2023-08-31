/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:37:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/31 12:57:47 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	not_found(t_cmd *node)
{
	ft_printf("mini: command not found:");
	ft_printf(" %s\n", node->cmd);
	free(node->cmd);
	free(node);
}

void	absolute_not_found(t_cmd *node)
{
	ft_printf("mini: No such file or directory: ");
	ft_printf("%s\n", node->cmd);
	free(node->cmd);
	free(node);
}

// void	remove_path(t_cmd *node)
// {
// 	int		i;
// 	int		len;
// 	char	*new_cmd;

// 	len = 0;
// 	i = 0;
// 	while (node->cmd[i])
// 		i++;
// 	while (node->cmd[--i] != '/')
// 		len++;
// 	i++;
// 	new_cmd = ft_calloc(sizeof(char), len + 1);
// 	len = 0;
// 	while (node->cmd[i])
// 	{
// 		new_cmd[len] = node->cmd[i];
// 		len++;
// 		i++;
// 	}
// 	new_cmd[len] = '\0';
// 	free(node->cmd);
// 	node->cmd = ft_strdup(new_cmd);
// }

int	handle_absolute_path(t_cmd *node)
{
	if (access(node->cmd, F_OK | X_OK) == 0)
	{
		node->cmd_path = ft_strdup(node->cmd);
		return (1);
	}
	else
	{
		absolute_not_found(node);
		return (0);
	}
}

int	access_path(char **env, t_cmd *node)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = node->cmd;
		path = ft_strdup(env[i]);
		path = ft_strjoin(path, "/");
		tmp = ft_strjoin(path, tmp);
		if (access(tmp, F_OK | X_OK) == 0)
		{
			node->cmd_path = ft_strdup(tmp);
			free(tmp);
			return (1);
		}
		i++;
		free(tmp);
	}
	not_found(node);
	return (0);
}

int	handle_path(char **env, t_cmd *node)
{
	if (node->cmd[0] == '/' || (node->cmd[0] == '.' && node->cmd[1] == '/'))
	{
		if (handle_absolute_path(node))
			return (1);
		else
			return (0);
	}
	if (access_path(env, node))
		return (1);
	else
		return (0);
}

int	args_size(t_token *current)
{
	int	i;

	i = 0;
	while (current && (current->type == ARG || current->type == CMD))
	{
		current = current->next;
		i++;
	}
	return (i);
}

int	handle_args(t_token *current, t_cmd *node)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!current)
		return (0);
	len = args_size(current);
	node->cmd_args = ft_calloc(sizeof(char *), len + 1);
	while (current && (current->type == ARG || current->type == CMD))
	{
		node->cmd_args[i] = ft_strdup(current->str);
		current = current->next;
		i++;
	}
	node->cmd_args[i] = NULL;
	return (1);
}

void	add_cmd_node(t_cmd *node, t_cmd **head)
{
	t_cmd	*current;

	if (*head == NULL)
	{
		*head = node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
	}
}

int	new_cmd(t_mini *mini, t_cmd **head, t_token *start)
{
	t_cmd	*node;
	t_token	*token;

	token = start;
	node = malloc(sizeof(t_cmd));
	if (!node || !start)
		return (0);
	node->cmd = ft_strdup(token->str);
	if (!handle_path(mini->env, node))
		return (0);
	if (!handle_args(token, node))
		return (0);
	node->next = NULL;
	add_cmd_node(node, head);
	return (1);
}

void	print_args(t_mini *mini)
{
	int		i;
	t_cmd	*current;

	i = -1;
	if (mini->cmd_tab == NULL)
		return ;
	current = mini->cmd_tab;
	while (current)
	{
		ft_printf("cmd : %s\n", current->cmd);
		ft_printf("path : %s\n", current->cmd_path);
		while (current->cmd_args[++i])
			ft_printf("args : %s\n", current->cmd_args[i]);
		current = current->next;
		i = -1;
	}
}

t_token	*move_to_first(t_token *current)
{
	// ajouter la variable HEREDOC && INPUT
	// APPEND ?? TRUNC ??
	if (current != NULL && (current->type != ARG && current->type != CMD))
		current = current->next;
	if (current != NULL && current->prev && (current->prev->type == INPUT
			|| current->prev->type == HEREDOC))
		current = current->next;
	return (current);
}

t_token	*move_to_next(t_token *current)
{
	// ajouter la variable HEREDOC && INPUT
	// APPEND ?? TRUNC ??
	// PIPE VIDE
	while (current != NULL && (current->type != PIPE))
	{
		current = current->next;
	}
	return (current);
}

void	cmd_args(t_mini *mini, int is_pipe)
{
	t_token	*current;

	current = mini->start;
	if (is_pipe == 0)
	{
		current = move_to_first(current);
		if (!new_cmd(mini, &mini->cmd_tab, current))
			return ;
	}
	else
	{
		while (current != NULL)
		{
			if (move_to_first(current))
				current = move_to_first(current);
			else
				return ;
			if (!new_cmd(mini, &mini->cmd_tab, current))
			{
				if (move_to_next(current))
					current = move_to_next(current);
				else
					return ;
			}
			else
				current = move_to_next(current);
		}
	}
}

void	is_pipe(t_mini *mini)
{
	t_token	*current;
	int		is_pipe;

	is_pipe = 0;
	if (mini->start == NULL)
		return ;
	current = mini->start;
	while (current)
	{
		if (current->type == PIPE)
		{
			is_pipe = 1;
			// Variables pipe a 1 on est dans une ligne de commande pipe
		}
		current = current->next;
	}
	cmd_args(mini, is_pipe);
	return ;
}

void	free_cmd(t_mini *mini)
{
	int		i;
	t_cmd	*current;
	t_cmd	*next;

	current = mini->cmd_tab;
	i = 0;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		free(current->cmd_path);
		while (current->cmd_args[i])
		{
			free(current->cmd_args[i]);
			i++;
		}
		free(current->cmd_args);
		i = 0;
		free(current);
		current = next;
	}
	mini->cmd_tab = NULL;
}

int	execution(t_mini *mini)
{
	is_pipe(mini);
	// char *const str_ls[3] = {"/usr/bin/ls", "-l", NULL}; // Commande "ls -l"

	// Exécution de la commande "ls -l"
	// if (fork() == 0)
	// {
	// 	execve("/usr/bin/ls", str_ls, NULL);
	// 	perror("execve ls");
	// 	exit(EXIT_FAILURE);
	// }

	// // Exécution de la commande inexistante "xyz123"
	// if (fork() == 0) {
	//     execve("/votre_chemin/xyz123", str_xyz, NULL);
	//     perror("execve xyz123");
	//     exit(EXIT_FAILURE);
	// }

	// // Attendre que les processus fils se terminent
	// wait(NULL);
	// wait(NULL);
	return (0);
}