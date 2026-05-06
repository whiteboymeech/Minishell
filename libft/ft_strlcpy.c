/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:28:49 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/15 17:28:49 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	x;
	size_t	countain;

	countain = ft_strlen(src);
	x = 0;
	if (size == 0)
		return (countain);
	while (src[x] && x < size - 1)
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = 0;
	return (countain);
}
