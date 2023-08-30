/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:27:05 by hdupuy            #+#    #+#             */
/*   Updated: 2023/01/30 10:35:35 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_int_char(int nmb, char *ret, size_t pos)
{
	char	to_char;

	nmb += 48;
	to_char = (char)nmb;
	ret[pos] = to_char;
	return (ret);
}

static char	*ft_fill_malloc(int nb, char *ret, size_t pos)
{
	if (nb == -2147483648)
	{
		ret[0] = '-';
		ret[1] = '2';
		ft_fill_malloc(147483648, ret, pos);
	}
	else if (nb < 0)
	{
		ret[0] = '-';
		ft_fill_malloc(nb * -1, ret, pos);
	}
	else if (nb > 0)
	{
		ft_fill_malloc(nb / 10, ret, --pos);
	}
	return (ft_int_char(nb % 10, ret, pos));
}

static char	*ft_zero(char *ret, int nb)
{
	ret = ft_int_char(nb, ret, 0);
	ret[1] = '\0';
	return (ret);
}

char	*ft_itoa(int n)
{
	long int	tmp;
	size_t		len;
	char		*ret;

	tmp = n;
	len = 0;
	if (tmp < 0)
	{
		tmp *= -1;
		len++;
	}
	while (tmp > 9)
	{
		tmp = tmp / 10;
		len++;
	}
	len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	if (n == 0)
		return (ft_zero(ret, n));
	ret = ft_fill_malloc(n, ret, len);
	ret[len] = '\0';
	return (ret);
}
