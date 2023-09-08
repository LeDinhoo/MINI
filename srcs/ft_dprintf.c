/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbacquet <cbacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:23:46 by cbacquet          #+#    #+#             */
/*   Updated: 2023/09/08 16:43:37 by cbacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mini.h"



static ssize_t	ft_base_fd(size_t nbr, char *base, int fd);
static int		print_required(char c, va_list args, int fd);
static size_t	ft_putchar_fd2(char c, int fd);
static size_t	ft_putstr_fd2(char *s, int fd);
size_t	ft_putnbr_fd2(int n, int fd, size_t size);


size_t	ft_putnbr_fd2(int n, int fd, size_t size)
{
	if (n == -2147483647 -1)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	else if (n < 0)
	{
		ft_putchar_fd2('-', fd);
		return ((ft_putnbr_fd2((-1 * n), fd, size)) + 1);
	}
	else if (n >= 10)
	{
		size += ft_putnbr_fd2((n / 10), fd, size);
		size += ft_putchar_fd2((n % 10 + '0'), fd);
	}
	else
		return (ft_putchar_fd2((n + '0'), fd));
	return (size);
}

static size_t	ft_putstr_fd2(char *s, int fd)
{
	if (s)
		return (write(fd, s, ft_strlen(s)));
	else
		return (write(fd, "(null)", 6));
}

static size_t	ft_putchar_fd2(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_dprintf(int fd, char *txt, ...)
{
	va_list	args;
	int		i;
	int		final_size;

	if (write(fd, 0, 0) == -1)
		return (-1);
	va_start(args, txt);
	final_size = 0;
	if (!txt)
		return (0);
	while (*txt)
	{
		i = 0;
		while (txt[i] && txt[i] != '%')
			i++;
		final_size += write(fd, txt, i);
		if (txt[i] == '%')
		{
			final_size += print_required(txt[++i], args, fd);
			txt++;
		}
		txt += i;
	}
	return (final_size);
}

static ssize_t	ft_base_fd(size_t nbr, char *base, int fd)
{
	size_t	size;
	size_t	lenbase;

	size = 0;
	lenbase = ft_strlen(base);
	if (nbr >= lenbase)
		size += ft_base_fd(nbr / lenbase, base, fd);
	size += ft_putchar_fd2(base[nbr % lenbase], fd);
	return (size);
}

static int	print_required(char c, va_list args, int fd)
{
	size_t	buff;

	buff = 0;
	if (c == 'c')
		return (ft_putchar_fd2(va_arg(args, int), fd));
	if (c == 's')
		return (ft_putstr_fd2(va_arg(args, char *), fd));
	if (c == 'u')
		return (ft_base_fd(va_arg(args, unsigned int), "0123456789", fd));
	if (c == 'i' || c == 'd')
		return (ft_putnbr_fd2(va_arg(args, int), fd, 0));
	if (c == 'x')
		return (ft_base_fd(va_arg(args, unsigned int), "0123456789abcdef", fd));
	if (c == 'X')
		return (ft_base_fd(va_arg(args, unsigned int), "0123456789ABCDEF", fd));
	if (c == '%')
		return (ft_putchar_fd2('%', fd));
	if (c == 'p')
	{
		buff += ft_putstr_fd2("0x", fd);
		return (buff += ft_base_fd(va_arg(args, size_t), \
		"0123456789abcdef", fd));
	}
	return (0);
}
