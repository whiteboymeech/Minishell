/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:20:10 by adarolla          #+#    #+#             */
/*   Updated: 2026/02/12 19:35:39 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strspn(char *s, char *accept)
{
	char	*tmp;

	tmp = s;
	while (*s)
	{
		if (!ft_strchr(accept, *s))
			break ;
		s++;
	}
	return (s - tmp);
}
