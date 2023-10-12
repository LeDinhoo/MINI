/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:37:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/12 13:01:20 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	clean_redir(t_mini *mini)
{
	dup2(mini->savein, 0);
	dup2(mini->saveout, 1);
	dup2(mini->saveerr, 2);
}

int	one_cmd(t_mini *mini, t_cmd *current)
{
	int	ret;

	ret = SUCCESS;
	redir_and_ret(current, &ret, mini);
	if (current->cmd)
	{
		ret = exec_bin(current, mini);
		clean_redir(mini);
		return (ret);
	}
	else
		return (ret);
}

int	execute_cmd(t_mini *mini, t_cmd *current, int pipe_fd[2], int i)
{
	int	ret;

	ret = SUCCESS;
	if (current->cmd && current->is_last == 1)
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	pipe_redirection(mini, current, pipe_fd, i);
	redir_and_ret(current, &ret, mini);
	if (current->cmd)
	{
		if (ft_strchr(current->cmd_path, '/') != NULL && !is_builtin(current))
			execve(current->cmd_path, current->cmd_args, mini->envp);
		else if (is_builtin(current))
		{
			exec_bin(current, mini);
		}
		if (!is_builtin(current))
			ret = update_ret(current, ret);
		free_all(mini);
		exit(ret);
	}
	else
	{
		free_all(mini);
		exit(ret);
	}
}

int	execution(t_mini *mini)
{
	cmd_args(mini);
	mini->nb_steps = cmd_numbers(mini->cmd_tab);
	if (is_only(mini) == 0)
		return (0);
	set_last_cmd(mini);
	iterate_commands(mini);
	if (is_builtin(mini->cmd_tab) && !mini->cmd_tab->next)
		wait_for_children();
	else
		mini->ret = wait_for_children();
	return (0);
}
