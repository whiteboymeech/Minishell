/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:22:33 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 18:22:55 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static t_tok	*collect_segment_fds(t_tok *curr, t_tok **exe,
	int *fd_in, int *fd_out)
{
	*exe = NULL;
	*fd_in = -1;
	*fd_out = -1;
	while (curr && curr->type != TOKEN_PIPE && curr->type != TOKEN_EOF)
	{
		if (curr->is_exe == 1)
			*exe = curr;
		if (curr->type == TOKEN_HEREDOC)
			*fd_in = curr->pipe.p[0];
		else if (curr->type == TOKEN_REDIR_IN && curr->fd_in != -1)
			*fd_in = curr->fd_in;
		else if ((curr->type == TOKEN_REDIR_OUT || curr->type == TOKEN_APPEND)
			&& curr->fd_out != -1)
			*fd_out = curr->fd_out;
		curr = curr->next;
	}
	return (curr);
}

void	apply_redir_fds(t_tok *lexed)
{
	t_tok	*curr;
	t_tok	*exe;
	int		fd_in;
	int		fd_out;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		curr = collect_segment_fds(curr, &exe, &fd_in, &fd_out);
		if (exe)
		{
			if (fd_in != -1)
				exe->fd_in = fd_in;
			if (fd_out != -1)
				exe->fd_out = fd_out;
		}
		if (curr && curr->type == TOKEN_PIPE)
			curr = curr->next;
	}
}
