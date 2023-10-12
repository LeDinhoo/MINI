/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:40:53 by cbacquet          #+#    #+#             */
/*   Updated: 2023/10/12 13:03:41 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	set_signal_handlers(t_mini *mini)
{
	sigaction(SIGINT, mini->sig->int_parent, NULL);
	sigaction(SIGQUIT, mini->sig->quit_parent, NULL);
}

void	exec_command(t_mini *mini, t_cmd *current, int pipe_fd[2], int i)
{
	sigaction(SIGINT, mini->sig->int_exec, NULL);
	execute_cmd(mini, current, pipe_fd, i);
	sigaction(SIGINT, mini->sig->int_parent, NULL);
}

void	close_pipe(t_mini *mini, int pipe_fd[2])
{
	close(pipe_fd[1]);
	mini->input_fd = pipe_fd[0];
}

void	iterate_commands(t_mini *mini)
{
	int		i;
	int		pipe_fd[2];
	t_cmd	*current;
	pid_t	pid;

	i = 0;
	current = mini->cmd_tab;
	mini->input_fd = 0;
	sigaction(SIGQUIT, mini->sig->quit_parent, NULL);
	while (current)
	{
		if (is_builtin(current) && !current->next)
			return (mini->ret = one_cmd(mini, current), (void) 0);
		if (current->is_last == 0)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			exec_command(mini, current, pipe_fd, i);
		if (i != 0)
			close(mini->input_fd);
		if (current->is_last == 0)
			close_pipe(mini, pipe_fd);
		current = current->next;
		i++;
	}
}
