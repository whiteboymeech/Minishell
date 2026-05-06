/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:27:57 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/16 11:27:57 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	lensrc;
	size_t	lendst;
	size_t	totalsize;

	lensrc = ft_strlen(src);
	if (size == 0)
		return (lensrc);
	lendst = ft_strlen(dst);
	totalsize = lendst + lensrc;
	if (size <= lendst)
		return (lensrc + size);
	ft_strlcpy(dst + lendst, src, size - lendst);
	return (totalsize);
}
