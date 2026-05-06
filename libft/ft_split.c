/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:57:48 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/19 14:57:48 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	freeall(char **str, size_t j)
{
	while (j > 0)
	{
		free(str[j - 1]);
		j--;
	}
	free(str);
}

static int	get_all(const char *s, char c)
{
	int	countain;
	int	i;

	i = 0;
	countain = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			countain++;
		i++;
	}
	return (countain);
}

static char	*get_str(char *str, const char *s, size_t countain)
{
	size_t	i;

	i = 0;
	while (i < countain)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**get_little_str(char **str, const char *s, char c, size_t i)
{
	size_t	j;
	size_t	start;

	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			str[j] = malloc((i - start) + 1);
			if (!str[j])
			{
				freeall(str, j);
				return (NULL);
			}
			str[j] = get_str(str[j], &s[start], i - start);
			j++;
		}
	}
	str[j] = NULL;
	return (str);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc((get_all(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	if (!get_little_str(str, s, c, i))
		return (NULL);
	return (str);
}
