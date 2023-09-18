/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:25:15 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 14:30:31 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	apply_output(t_cmd *current)
{
	int	output_fd;

	output_fd = 0;
	output_fd = open(current->redir.output_file, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (output_fd == -1)
	{
		perror("Invalid file descriptor");
		return (0);
	}
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	return (1);
}

int	apply_append(t_cmd *current)
{
	int	append_fd;

	append_fd = 0;
	append_fd = open(current->redir.append_file, O_CREAT | O_RDWR | O_APPEND,
			0644);
	if (append_fd == -1)
	{
		perror("Invalid file descriptor");
		return (0);
	}
	dup2(append_fd, STDOUT_FILENO);
	close(append_fd);
	return (1);
}

int	apply_input(t_cmd *current)
{
	int	input_fd;

	input_fd = 0;
	input_fd = open(current->redir.input_file, O_RDONLY);
	if (input_fd == -1)
	{
		perror("Invalid file descriptor");
		return (0);
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	return (1);
}

int	apply_heredoc(void)
{
	int	heredoc_fd;

	heredoc_fd = 0;
	heredoc_fd = open("/tmp/.pipex_here_doc", O_RDONLY);
	if (heredoc_fd == -1)
	{
		perror("Invalid file descriptor");
		return (0);
	}
	dup2(heredoc_fd, STDIN_FILENO);
	close(heredoc_fd);
	return (1);
}

int	apply_redirection(t_cmd *current)
{
	int	ret;

	ret = 1;
	if (current->redir.output_file)
		ret = apply_output(current);
	if (current->redir.append_file)
		ret = apply_append(current);
	if (current->redir.input_file)
		ret = apply_input(current);
	if (current->redir.heredoc_content)
		ret = apply_heredoc();
	return (ret);
}
