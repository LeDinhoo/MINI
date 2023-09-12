/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:37 by clement           #+#    #+#             */
/*   Updated: 2023/09/12 16:09:38 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_init_signals(t_sig *sig)
{
	sig->int_prompt = calloc(1, sizeof(struct sigaction));
	sig->int_exec = calloc(1, sizeof(struct sigaction));
	// sig->int_parent = calloc(1, sizeof(struct sigaction));
	sig->here_doc = calloc(1, sizeof(struct sigaction));
	sig->quit_prompt = calloc(1, sizeof(struct sigaction));
	sig->quit_exec = calloc(1, sizeof(struct sigaction));
	// sig->quit_parent = calloc(1, sizeof(struct sigaction));
	ft_check_malloc(sig);
	ft_set_signals_handle(sig);
	ft_init_quit_handle(sig);
}

void	ft_check_malloc(t_sig *sig)
{
	if (!sig->int_prompt || !sig->here_doc || !sig->int_exec
		|| !sig->quit_exec || !sig->quit_prompt)
	{
		write(1, "you have to init sigaction\n", 27);
		if (sig->int_prompt)
			free(sig->int_prompt);
		if (sig->int_exec)
			free(sig->int_exec);
		if (sig->here_doc)
			free(sig->here_doc);
		if (sig->quit_exec)
			free(sig->quit_exec);
		if (sig->quit_prompt)
			free(sig->quit_prompt);
		exit(EXIT_FAILURE);
	}
}
