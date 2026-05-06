/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 14:51:51 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 14:25:53 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	is_n_flag(char *value)
{
	int	i;

	if (!value || value[0] != '-')
		return (0);
	i = 1;
	while (value[i] == 'n')
		i++;
	return (value[i] == '\0');
}

int	echo(t_tok *tokens)
{
	int		flag;
	int		fd;
	t_tok	*tok;

	flag = 1;
	if (tokens && tokens->prev)
		fd = tokens->prev->fd_out;
	else
		fd = 1;
	tok = tokens;
	while (tok && tok->type == TOKEN_WORD && is_n_flag(tok->value))
	{
		flag = 0;
		tok = tok->next;
	}
	while (tok && tok->type == TOKEN_WORD)
	{
		ft_putstr_fd(tok->value, fd);
		if (tok->next && tok->next->type == TOKEN_WORD)
			write(fd, " ", 1);
		tok = tok->next;
	}
	if (flag)
		write(fd, "\n", 1);
	return (0);
}
