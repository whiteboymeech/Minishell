/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:21:26 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/16 15:21:26 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*xo;

	xo = NULL;
	while (*s)
	{
		if (*s == (char)c)
			xo = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)xo);
}
