/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:43:36 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/20 19:43:36 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	get_size_nb(int nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		size++;
	while (nb != 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*res;
	int		size;
	int		i;
	long	n;

	size = get_size_nb(nb);
	n = nb;
	i = size - 1;
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		res[0] = 45;
		n = -n;
	}
	while (n != 0)
	{
		res[i--] = n % 10 + '0';
		n = n / 10;
	}
	res[size] = '\0';
	return (res);
}
