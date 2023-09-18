/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/18 10:24:04 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	init_struct(t_mini *mini, char **envp)
{
    mini->is_here_doc = 0;
    mini->input = NULL;
    mini->env = NULL;
	mini->start = NULL;
    mini->cmd_tab = NULL;
    mini->envp = NULL;
    mini->envp = envp;
    get_path(mini);
}
