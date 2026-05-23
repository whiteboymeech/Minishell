/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:22:33 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/23 22:44:12 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	handle_redir_token(t_tok *curr, int *fd_in, int *fd_out,
		int *redir_failed)
{
	if (curr->type == TOKEN_HEREDOC)
		*fd_in = curr->pipe.p[0];
	else if (curr->type == TOKEN_REDIR_IN)
	{
		if (curr->fd_in == -1)
			*redir_failed = 1;
		else
			*fd_in = curr->fd_in;
	}
	else if (curr->type == TOKEN_REDIR_OUT || curr->type == TOKEN_APPEND)
	{
		if (curr->fd_out == -1)
			*redir_failed = 1;
		else
			*fd_out = curr->fd_out;
	}
}

static t_tok	*collect_segment_fds(t_tok *curr, t_seg_fds *seg)
{
	seg->exe = NULL;
	seg->fd_in = -1;
	seg->fd_out = -1;
	seg->redir_failed = 0;
	while (curr && curr->type != TOKEN_PIPE && curr->type != TOKEN_EOF)
	{
		if (curr->is_exe == 1)
			seg->exe = curr;
		handle_redir_token(curr, &seg->fd_in, &seg->fd_out, &seg->redir_failed);
		curr = curr->next;
	}
	return (curr);
}

void	apply_redir_fds(t_tok *lexed)
{
	t_tok		*curr;
	t_seg_fds	seg;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		curr = collect_segment_fds(curr, &seg);
		if (seg.exe)
		{
			if (seg.redir_failed)
				seg.exe->fd_in = -1;
			else
			{
				if (seg.fd_in != -1)
					seg.exe->fd_in = seg.fd_in;
				if (seg.fd_out != -1)
					seg.exe->fd_out = seg.fd_out;
			}
		}
		if (curr && curr->type == TOKEN_PIPE)
			curr = curr->next;
	}
}
