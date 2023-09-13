/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/13 13:48:15 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	init_struct(t_mini *mini)
{
    mini->is_here_doc = 0;
    mini->input = NULL;
    mini->env = NULL;
	mini->start = NULL;
    mini->cmd_tab = NULL;
    mini->envp = NULL;
    mini->envp = ft_calloc(2, sizeof(char *));
    mini->envp[0] = ft_strdup("PATH=");
    mini->envp[0] = ft_strjoin(mini->envp[0], getenv("PATH"));
    mini->envp[1] = NULL;
    get_path(mini);
}
