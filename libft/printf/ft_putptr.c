/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:58:32 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/31 13:58:32 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putptr(long long unsigned i, int *val, char *base)
{
	if (!i)
	{
		write(2, "(nil)", 5);
		(*val) += 5;
	}
	else
	{
		write(2, "0x", 2);
		ft_puthexa(i, base, val);
		(*val) += 2;
	}
}
