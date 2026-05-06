/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 12:39:02 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/18 12:39:02 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*my_strcpy(char *tab, char *dest, char *src)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[i])
	{
		tab[i] = dest[i];
		i++;
	}
	while (src[j])
	{
		tab[i + j] = src[j];
		j++;
	}
	tab[i + j] = '\0';
	return (tab);
}

static char	*tabzero(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*tab;
	size_t	totaletters;

	tab = NULL;
	if (!s1 || !s2)
		return (NULL);
	if ((s1[0] == 0) && (s2[0] == 0))
		return (tabzero());
	totaletters = ft_strlen(s1) + ft_strlen(s2);
	tab = malloc(totaletters + 1);
	if (!tab)
		return (NULL);
	my_strcpy(tab, s1, s2);
	return (tab);
}
