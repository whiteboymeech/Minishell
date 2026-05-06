/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:11:16 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/03 18:51:08 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == '\n')
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

unsigned int	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	size_t	totaletters;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
		totaletters = ft_strlen(s2);
	else
		totaletters = ft_strlen(s1) + ft_strlen(s2);
	tab = ft_calloc(totaletters + 1, 1);
	if (!tab)
		return (NULL);
	if (s1)
		while (s1[++i])
			tab[++j] = s1[i];
	i = -1;
	while (s2[++i])
		tab[++j] = s2[i];
	free(s1);
	return (tab);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			total;
	size_t			i;
	unsigned char	*bytes;

	total = nmemb * size;
	if (nmemb != 0 && size > total / nmemb)
		return (NULL);
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	bytes = (unsigned char *)ptr;
	i = 0;
	while (i < total)
		bytes[i++] = 0;
	return (ptr);
}
