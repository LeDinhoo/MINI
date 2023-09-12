/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:02 by clement           #+#    #+#             */
/*   Updated: 2023/09/12 15:54:19 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_init_quit_handle(t_sig *sig)
{
	sig->quit_prompt->sa_handler = SIG_IGN;
	sig->quit_prompt->sa_flags = SA_RESTART;
	sigemptyset(&sig->quit_prompt->sa_mask);
}

void	ft_handle_signal(int sig_prompt)
{
	(void)sig_prompt;
	write(1, "\n", 1);
	// ft_dprintf(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_handle_signal_heredoc(int sig_heredoc)
{
	(void)sig_heredoc;
	close(STDIN_FILENO);
	write(1, "\n", 1);
}

void	ft_set_signals_handle(t_sig *sig)
{
	sig->int_prompt->sa_handler = ft_handle_signal;
	sig->int_prompt->sa_flags = SA_RESTART;
	sigemptyset(&sig->int_prompt->sa_mask);
	sig->int_exec->sa_handler = SIG_IGN;
	sig->int_exec->sa_flags = SA_RESTART;
	sigemptyset(&sig->int_exec->sa_mask);
	sig->int_exec->sa_handler = SIG_DFL;
	sig->int_exec->sa_flags = SA_RESTART;
	sigemptyset(&sig->int_exec->sa_mask);
	sig->here_doc->sa_handler = ft_handle_signal_heredoc;
	sig->here_doc->sa_flags = SA_RESTART;
	sigemptyset(&sig->here_doc->sa_mask);
	
}
