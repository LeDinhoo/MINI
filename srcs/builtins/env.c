/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clement <clement@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:33:54 by clement           #+#    #+#             */
/*   Updated: 2023/09/21 18:56:08 by clement          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*bool	ft_check_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (true);
		i++;
	}
	return (false);
}*/

void	env(char **envp)
{
	int	i;
	
	i = 0;
	while(envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}
