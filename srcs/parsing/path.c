/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:57:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/03 14:25:20 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	get_path(t_mini *mini)
{
	char	*str;

	str = get_env("PATH", mini->envp);
	if (!str)
	{
		mini->path = ft_calloc(1, sizeof(char *));
		return ;
	}
	mini->path = ft_split(str, ':');
}
