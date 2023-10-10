/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 13:18:50 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/02 11:56:26 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	echo_build(t_cmd *current)
{
	int	i;
	int	n;
	int	option;

	i = 1;
	n = 0;
	option = 1;
	while (current->cmd_args[i])
	{
		while (option == 1 && ft_strcmp(current->cmd_args[i], "-n") == 0)
		{
			n = 1;
			i++;
		}
		printf("%s", current->cmd_args[i]);
		option = 0;
		if (current->cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (n == 0)
		printf("\n");
	return (0);
}
