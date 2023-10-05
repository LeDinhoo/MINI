/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/03 14:25:06 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_list(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void	free_env(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->path[i])
	{
		free(mini->path[i]);
		i++;
	}
	free(mini->path);
	mini->path = NULL;
}

void	free_redir(t_cmd *current)
{
	free(current->redir.append_file);
	free(current->redir.heredoc_content);
	free(current->redir.input_file);
	free(current->redir.output_file);
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
		while (current->cmd_args && current->cmd_args[i])
		{
			free(current->cmd_args[i]);
			i++;
		}
		free_redir(current);
		free(current->cmd_args);
		i = 0;
		free(current);
		current = next;
	}
	mini->cmd_tab = NULL;
}

void	free_all(t_mini *mini)
{
	free_list(mini->start);
	free_cmd(mini);
	free(mini->input);
	free_env(mini);
}
