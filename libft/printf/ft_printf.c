/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 14:38:05 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/26 14:38:05 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	findtype(char a, va_list arg)
{
	int	val;

	val = 0;
	if (a == 'c')
		val += ft_putchar(va_arg(arg, int));
	else if (a == 's')
		val += ft_putstr(va_arg(arg, char *));
	else if (a == 'x')
		ft_puthexa(va_arg(arg, unsigned int), "0123456789abcdef", &val);
	else if (a == 'X')
		ft_puthexa(va_arg(arg, unsigned int), "0123456789ABCDEF", &val);
	else if (a == 'p')
		ft_putptr(va_arg(arg, long unsigned), &val, "0123456789abcdef");
	else if (a == '%')
		val += (ft_putchar('%'));
	else if (a == 'd' || a == 'i')
		val += ft_putnbr(va_arg(arg, int));
	else if (a == 'u')
		val += ft_putunsigned(va_arg(arg, unsigned int));
	else
		val += (ft_putchar(a));
	return (val);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (format == NULL)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += findtype(format[++i], args);
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
