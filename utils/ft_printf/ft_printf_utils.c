/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:58:42 by hdupuy            #+#    #+#             */
/*   Updated: 2022/12/01 14:18:45 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	return (write (1, &c, 1));
}

int	ft_putstr(char *s)
{
	size_t	idx;

	idx = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[idx])
	{
		ft_putchar(s[idx]);
		idx++;
	}
	return (idx);
}

int	ft_putnbr(int nb)
{
	if (nb == -2147483648)
		return (ft_putstr("-2147483648"));
	if (nb < 0)
		return (write(1, "-", 1) + ft_putnbr(nb *= -1));
	if (nb < 10)
		return (ft_putchar(nb % 10 + 48));
	return (ft_putnbr(nb / 10) + ft_putchar(nb % 10 + 48));
}

int	ft_putunbr(unsigned int nb)
{
	if (nb < 10)
		return (ft_putchar(nb % 10 + 48));
	return (ft_putnbr(nb / 10) + ft_putchar(nb % 10 + 48));
}

int	ft_hex(unsigned long long nb, char *base)
{
	if (nb < 16)
		return (ft_putchar(base[nb % 16]));
	return (ft_hex(nb / 16, base) + ft_putchar(base[nb % 16]));
}
