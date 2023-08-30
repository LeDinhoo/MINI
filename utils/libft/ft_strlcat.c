/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:28:48 by hdupuy            #+#    #+#             */
/*   Updated: 2023/01/05 10:31:36 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	size_dest;
	unsigned int	size_src;

	i = 0;
	if ((!dst || !src) && !dstsize)
		return (0);
	size_dest = ft_strlen(dst);
	size_src = ft_strlen(src);
	if (size_dest + 1 > dstsize)
		return (dstsize + size_src);
	while (src[i] && size_dest + i < dstsize - 1)
	{
		dst[i + size_dest] = src[i];
		i++;
	}
	dst[i + size_dest] = '\0';
	return (size_dest + size_src);
}
