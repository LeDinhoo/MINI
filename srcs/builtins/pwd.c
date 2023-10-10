/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:33:12 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/05 16:33:55 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	pwd_build(void)
{
	char *str;

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