/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:30:13 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/18 22:30:13 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	chartofind(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	my_lcpy(char *dst, char *src, size_t size)
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

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	char	*str;
	size_t	allsize;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (end == 0)
		return (ft_strdup(""));
	end--;
	while (s1[start] && chartofind(s1[start], set))
		start++;
	while (end > start && chartofind(s1[end], set))
		end--;
	allsize = end - start + 1;
	str = malloc(allsize + 1);
	if (!str)
		return (NULL);
	my_lcpy(str, (char *)s1 + start, allsize + 1);
	return (str);
}
