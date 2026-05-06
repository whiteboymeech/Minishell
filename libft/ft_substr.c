/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:51:37 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/17 17:51:37 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*get_free_string(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	xo;
	char	*str;
	size_t	totsize;

	xo = -1;
	totsize = (ft_strlen(s) - start);
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		str = get_free_string();
		if (!str)
			return (NULL);
		return (str);
	}
	if (len > totsize)
		len = totsize;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (++xo < len && s[xo + start])
		str[xo] = s[start + xo];
	str[len] = '\0';
	return (str);
}
