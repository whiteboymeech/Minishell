/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:25:32 by adarolla          #+#    #+#             */
/*   Updated: 2026/02/12 21:26:07 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strcat(char c, char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_calloc(ft_strlen(str) + 2, 1);
	if (!s)
		return (NULL);
	s[0] = c;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	return (s);
}
