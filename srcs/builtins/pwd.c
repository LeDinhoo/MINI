/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:33:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/10 20:21:36 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	pwd_build(void)
{
	char	*str;

	str = getcwd(NULL, 0);
	if (str == NULL)
	{
		dprintf(STDERR_FILENO, "mini: pwd: %s\n", strerror(errno));
		return (1);
	}
	else
		printf("%s\n", str);
	free(str);
	return (0);
}
