/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 14:40:50 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/08 19:01:13 by adarolla         ###   ########.fr       */
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
	ft_putstr_fd(ret, tokens->fd_out);
	ft_putstr_fd("\n", tokens->fd_out);
	return (0);
}
