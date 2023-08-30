/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdupuy <hdupuy@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:49:58 by hdupuy            #+#    #+#             */
/*   Updated: 2023/01/03 17:59:46 by hdupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_wich_type(char type, va_list s_arg)
{
	int	i;

	i = 0;
	if (type == 'c')
		i += ft_putchar(va_arg(s_arg, int));
	else if (type == 's')
		i += (ft_putstr(va_arg(s_arg, char *)));
	else if (type == 'i' || type == 'd')
		i += ft_putnbr(va_arg(s_arg, int));
	else if (type == 'u')
		i += ft_putunbr(va_arg(s_arg, unsigned int));
	else if (type == 'x')
		i += ft_hex(va_arg(s_arg, unsigned int), "0123456789abcdef");
	else if (type == 'X')
		i += ft_hex(va_arg(s_arg, unsigned int), "0123456789ABCDEF");
	else if (type == 'p')
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		i += 2;
		i += ft_hex(va_arg(s_arg, long), "0123456789abcdef");
	}
	else
		i += ft_putchar(type);
	return (i);
}

int	ft_printf(const char *s, ...)
{
	va_list	s_arg;
	size_t	idx;
	ssize_t	count;

	idx = 0;
	count = 0;
	if (write (1, 0, 0) == -1)
		return (-1);
	va_start(s_arg, s);
	while (s[idx])
	{
		if (s[idx] == '%' && s[idx + 1])
			count += (ft_wich_type(s[++idx], s_arg));
		else
			count += ft_putchar(s[idx]);
		idx++;
	}
	va_end(s_arg);
	return (count);
}
