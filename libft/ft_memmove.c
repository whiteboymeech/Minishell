/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 22:31:30 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/14 22:31:30 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			x;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	x = 0;
	if (dest == src || n == 0)
		return (dest);
	while (x < n)
	{
		if (d > s)
			d[n - x - 1] = s[n - x - 1];
		else
			d[x] = s[x];
		x++;
	}
	return (dest);
}
