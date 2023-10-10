/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:36 by hdupuy            #+#    #+#             */
/*   Updated: 2023/10/10 14:41:03 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *destination, const char *source, size_t num)
{
	while (*destination)
	{
		destination++;
	}
	while (*source && num > 0)
	{
		*destination = *source;
		destination++;
		source++;
		num--;
	}
	*destination = '\0';
	return (destination);
}