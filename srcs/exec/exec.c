/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:37:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/06 10:06:34 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	find_redirection(t_token *current, t_expect *ex)
{
	if (current->type == INPUT)
		ex->input = 1;
	else if (current->type == TRUNC)
		ex->output = 1;
	else if (current->type == APPEND)
		ex->append = 1;
	else if (current->type == HEREDOC)
		ex->heredoc = 1;
}

void	pipe_redirection(t_mini *mini, t_cmd *current, int pipe_fd[2], int i)
{
	if (i != 0)
	{
		if (mini->input_fd != 0)
		{
			dup2(mini->input_fd, STDIN_FILENO);
			close(mini->input_fd);
		}
	}
	if (current->cmd && current->is_last == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

static void	clean_redir(t_mini *mini)
{
	dup2(mini->savein, 0);
	dup2(mini->saveout, 1);
	dup2(mini->saveerr, 2);
}

int	one_command(t_mini *mini, t_cmd *current, int pipe_fd[2], int i)
{
	int	ret;

	ret = SUCCESS;
	redir_and_ret(current, &ret, mini);
	if (current->cmd)
	{
		exec_bin(current, mini);
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

void	iterate_commands(t_mini *mini)
{
	int		pipe_fd[2];
	int		i;
	t_cmd	*current;
	pid_t	pid;

	i = 0;
	current = mini->cmd_tab;
	mini->input_fd = 0;
	while (current)
	{
		sigaction(SIGQUIT, mini->sig->quit_parent, NULL);
		if (is_builtin(current) && !current->next)
		{
			one_command(mini, current, pipe_fd, i);
			return ;
		}
		if (current->is_last == 0)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
		{
			sigaction(SIGINT, mini->sig->int_exec, NULL);
			execute_cmd(mini, current, pipe_fd, i);
		}
		sigaction(SIGINT, mini->sig->int_parent, NULL);
		if (i != 0)
			close(mini->input_fd);
		if (current->is_last == 0)
		{
			close(pipe_fd[1]);
			mini->input_fd = pipe_fd[0];
		}
		current = current->next;
		i++;
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
	mini->ret = wait_for_children();
	return (0);
}
