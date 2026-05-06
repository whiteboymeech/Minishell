/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:04:51 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/29 12:06:26 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_puthexa(unsigned long long n, char *base, int *val)
{
	if (n >= 16)
	{
		ft_puthexa(n / 16, base, val);
		write(2, &(base[n % 16]), 1);
		(*val)++;
	}
	else if (n >= 0 && n <= 15)
	{
		write(2, &(base[n % 16]), 1);
		(*val)++;
	}
}
