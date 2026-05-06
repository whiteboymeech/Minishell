/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_allocated.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 04:14:45 by adarolla          #+#    #+#             */
/*   Updated: 2026/02/16 04:14:45 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strcat_allocated(char *dest, char *src)
{
	int		i;
	int		a;
	char	*tmp;

	tmp = malloc(ft_strlen(src) + ft_strlen(dest) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	a = 0;
	while (dest[i])
	{
		tmp[i] = dest[i];
		i++;
	}
	while (src[a])
	{
		tmp[i] = src[a];
		a++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
