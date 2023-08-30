/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dupuy <dupuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:20:10 by hdupuy            #+#    #+#             */
/*   Updated: 2023/05/17 15:19:31 by dupuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *s, ...);
int	ft_wich_type(char type, va_list s_arg);
int	ft_putstr(char *s);
int	ft_putnbr(int nb);
int	ft_putchar(char c);
int	ft_hex(unsigned long long nb, char *base);
int	ft_putunbr(unsigned int nb);

#endif
