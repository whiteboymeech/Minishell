/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:19:42 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/29 11:19:42 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_putunsigned(unsigned int nb)
{
	long unsigned int	n;
	unsigned int		count;

	n = nb;
	count = 0;
	if (n >= 10)
		count += ft_putunsigned(nb / 10);
	count += ft_putchar(nb % 10 + '0');
	return (count);
}
