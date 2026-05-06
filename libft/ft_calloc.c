/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:31:56 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/17 15:31:56 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*xo;
	size_t	bigsize;

	bigsize = nmemb * size;
	if (nmemb == 0 || size == 0)
	{
		xo = malloc(0);
		if (!xo)
			return (NULL);
		return (xo);
	}
	if (bigsize / size != nmemb)
		return (NULL);
	xo = malloc(bigsize);
	if (!xo)
		return (NULL);
	ft_bzero(xo, bigsize);
	return (xo);
}
