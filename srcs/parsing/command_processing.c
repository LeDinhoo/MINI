/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/04 17:34:12 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	is_cmd(t_token *current, char **env, int i)
{
	char	*cmd;
	char	*path;

	while (env[i])
	{
		cmd = current->str;
		path = ft_strdup(env[i]);
		path = ft_strjoin(path, "/");
		cmd = ft_strjoin(path, cmd);
		if (access(cmd, F_OK | X_OK) == 0)
			current->type = CMD;
		i++;
		free(cmd);
	}
}

void	update_token_types(t_mini *mini)
{
	t_token	*current;
	int		i;
	int		redirection;

	i = 0;
	redirection = 0;
	current = mini->start;
	while (current != NULL)
	{
		if (current->next && redirection == 1)
		{
			current = current->next;
			current->type = CMD;
			redirection = 0;
		}
		if (!current->prev || current->prev->type == PIPE)
		{
			if (current->type == HEREDOC || current->type == INPUT
				|| current->type == APPEND || current->type == TRUNC)
				redirection = 1;
			else
				current->type = CMD;
		}
		current = current->next;
	}
}
