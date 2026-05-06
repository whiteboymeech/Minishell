/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:46:49 by adarolla          #+#    #+#             */
/*   Updated: 2026/02/12 19:37:01 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtok(char *str, char *delim)
{
	static char	*tmp;
	char		*tok;
	int			i;

	i = 0;
	if (str)
		tmp = str;
	if (!tmp || !delim)
		return (NULL);
	if (tmp == NULL)
		return (NULL);
	tmp += ft_strspn(tmp, delim);
	if (*tmp == '\0')
		return (NULL);
	tok = tmp;
	i = ft_strcspn(tmp, delim);
	tmp += i;
	if (*tmp != '\0')
	{
		*tmp = 0;
		tmp++;
	}
	else
		tmp = NULL;
	return (tok);
}
