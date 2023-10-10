/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:35:01 by clement           #+#    #+#             */
/*   Updated: 2023/10/09 17:48:51 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_signals(t_mini *mini)
{
	ft_free_array(mini->envp);
	free(mini->sig->int_prompt);
	free(mini->sig->int_exec);
	free(mini->sig->int_parent);
	free(mini->sig->here_doc);
	free(mini->sig->quit_prompt);
	free(mini->sig->quit_exec);
	free(mini->sig->quit_parent);
	free(mini->sig);
}
