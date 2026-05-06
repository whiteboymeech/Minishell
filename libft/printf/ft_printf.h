/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libftprintf.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:13:38 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/28 16:13:38 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		findtype(char a, va_list arg);
int		ft_putchar(char c);
int		ft_printf(const char *format, ...);
int		ft_putnbr(int n);
int		ft_putstr(char *s);
int		ft_putunsigned(unsigned int nb);
void	ft_puthexa(unsigned long long n, char *base, int *val);
void	ft_putptr(long long unsigned i, int *val, char *base);

#endif
