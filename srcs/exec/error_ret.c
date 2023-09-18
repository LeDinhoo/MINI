/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:34:00 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 15:09:00 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	ft_close(fd);
	return (ret);
}

int	update_ret(t_cmd *current, int ret)
{
	if (current->cmd_path != NULL)
		ret = error_message(current->cmd_path);
	else
		ret = error_message(current->cmd);
	return (ret);
}

void	redir_and_ret(t_cmd *current, int *ret, t_mini *mini)
{
	if (current->redir.output_file || current->redir.input_file
		|| current->redir.append_file || current->redir.heredoc_content)
	{
		if (apply_redirection(current) == 0)
		{
			*(ret) = update_ret(current, (*(ret)));
			free_all(mini);
			exit(*(ret));
		}
	}
}

int	wait_for_children(void)
{
	int		last_child_exit_status;
	int		status;
	pid_t	child_pid;

	last_child_exit_status = 0;
	child_pid = wait(&status);
	while (child_pid != -1)
	{
		if (WIFEXITED(status))
			last_child_exit_status = WEXITSTATUS(status);
		child_pid = wait(&status);
	}
	return (last_child_exit_status);
}
