/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 14:40:50 by adarolla          #+#    #+#             */
/*   Updated: 2026/04/25 23:35:19 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	pwd(t_tok *tokens)
{
	char	ret[PATH_MAX];

	if (getcwd(ret, PATH_MAX) == NULL)
	{
		perror("pwd:");
		return (1);
	}
	ft_putstr_fd(ret, tokens->prev->fd_out);
	ft_putstr_fd("\n", tokens->prev->fd_out);
	return (0);
}
