/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 13:05:18 by hdupuy            #+#    #+#             */
/*   Updated: 2023/08/30 12:27:32 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	builtin_exec(t_mini *mini)
{
	t_token	*current;

	if (mini->start == NULL)
		return ;
	current = mini->start;
	if (ft_strcmp(current->str, "cd") == 0)
		cd_build(mini);
	if (ft_strcmp(current->str, "echo") == 0)
		echo_build(mini->start);
}
