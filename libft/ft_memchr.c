/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:47:04 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/16 15:47:04 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	xo;

	xo = 0;
	while (xo < n)
	{
		if (((unsigned char *)s)[xo] == (unsigned char)c)
			return (&((unsigned char *)s)[xo]);
		xo++;
	}
	return (NULL);
}
