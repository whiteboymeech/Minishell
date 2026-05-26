/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenois <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 04:55:23 by mabenois          #+#    #+#             */
/*   Updated: 2026/05/13 23:25:30 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	open_single_redir(t_tok *curr)
{
	if (!curr->next || curr->next->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		return (1);
	}
	if (curr->type == TOKEN_REDIR_OUT)
		curr->fd_out = open(curr->next->value, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR);
	else if (curr->type == TOKEN_APPEND)
		curr->fd_out = open(curr->next->value, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR);
	else if (curr->type == TOKEN_REDIR_IN)
		curr->fd_in = open(curr->next->value, O_RDONLY);
	if ((curr->type == TOKEN_REDIR_OUT || curr->type == TOKEN_APPEND)
		&& curr->fd_out == -1)
	{
		perror(curr->next->value);
		return (1);
	}
	if (curr->type == TOKEN_REDIR_IN && curr->fd_in == -1)
	{
		perror(curr->next->value);
		return (1);
	}
	return (0);
}

static void	mark_exe_token(t_tok *curr, int *is_arg)
{
	t_type	prev_type;

	prev_type = TOKEN_EOF;
	if (curr->prev)
		prev_type = curr->prev->type;
	if (prev_type != TOKEN_REDIR_IN && prev_type != TOKEN_REDIR_OUT
		&& prev_type != TOKEN_APPEND && prev_type != TOKEN_HEREDOC)
	{
		curr->is_exe = 1;
		*is_arg = 1;
	}
}

int	open_redir_fds(t_tok *lexed)
{
	t_tok	*curr;
	int		is_arg;
	int		err;

	is_arg = -1;
	err = 0;
	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_PIPE)
			is_arg = -1;
		if (curr->type == TOKEN_WORD && is_arg == -1)
			mark_exe_token(curr, &is_arg);
		if (curr->type == TOKEN_REDIR_OUT || curr->type == TOKEN_APPEND
			|| curr->type == TOKEN_REDIR_IN)
		{
			if (open_single_redir(curr))
				err = 1;
		}
		curr = curr->next;
	}
	return (err);
}
