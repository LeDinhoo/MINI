/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:28:00 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 14:30:24 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_input_redirection(t_cmd *cmd, const char *filename)
{
	cmd->redir.input_file = strdup(filename);
}

void	handle_output_redirection(t_cmd *cmd, const char *filename)
{
	cmd->redir.output_file = ft_strdup(filename);
}

void	handle_append_redirection(t_cmd *cmd, const char *filename)
{
	cmd->redir.append_file = strdup(filename);
}

void	handle_heredoc(t_cmd *cmd, const char *filename)
{
	cmd->redir.heredoc_content = strdup(filename);
}

int	handle_redirection(t_cmd *current_cmd, t_token *current, t_expect *ex)
{
	if (ex->input)
	{
		handle_input_redirection(current_cmd, current->str);
		ex->input = 0;
		return (1);
	}
	else if (ex->output)
	{
		handle_output_redirection(current_cmd, current->str);
		ex->output = 0;
		return (1);
	}
	else if (ex->append)
	{
		handle_append_redirection(current_cmd, current->str);
		ex->append = 0;
		return (1);
	}
	else if (ex->heredoc)
	{
		handle_heredoc(current_cmd, current->str);
		ex->heredoc = 0;
		return (1);
	}
	return (0);
}
