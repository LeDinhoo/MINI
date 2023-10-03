/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <dupuy@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 09:17:09 by hdupuy            #+#    #+#             */
/*   Updated: 2023/09/29 09:24:04 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*h;
	const char	*n;

	h = haystack;
	n = needle;
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		while (*h != '\0' && *n != '\0' && *h == *n)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
