/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:50:37 by adarolla          #+#    #+#             */
/*   Updated: 2026/02/12 20:29:32 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	x;

	x = 0;
	if (n == 0 || dest == src)
		return (dest);
	while (x < n)
	{
		((char *)dest)[x] = ((char *)src)[x];
		x++;
	}
	return (dest);
}
