/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:06:06 by adarolla          #+#    #+#             */
/*   Updated: 2025/10/17 17:06:06 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (big[0] == '\0' && little[0] == '\0')
		return (((char *)big));
	if (big[0] == '\0')
		return (NULL);
	if (little[0] == '\0')
		return (((char *)big));
	while (big[i] != '\0')
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j] && (little[j] != '\0'))
			j++;
		if (little[j] == '\0')
			return (&((char *)big)[i]);
		i++;
	}
	return (0);
}
