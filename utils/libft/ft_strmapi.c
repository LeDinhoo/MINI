/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:33:00 by hdupuy            #+#    #+#             */
/*   Updated: 2023/01/05 10:34:55 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	size_t			idx;
	size_t			len;
	char			*ret;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	idx = 0;
	while (len--)
	{
		ret[idx] = (f(idx, s[idx]));
		idx++;
	}
	ret[idx] = '\0';
	return (ret);
}
