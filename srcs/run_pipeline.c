/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:27:02 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 20:10:08 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	handle_boundary(t_tok *curr, t_pipe_state *st)
{
	pid_t	pid;

	if (!*st->has_exe && *st->pending)
	{
		pid = exec_empty_segment(st->fd_out, st->fd_in);
		if (pid > 0)
			*st->last = pid;
	}
	if (*st->pending)
	{
		close((*st->pending)->pipe.p[0]);
		*st->pending = NULL;
	}
	*st->has_exe = 0;
	if (curr->type == TOKEN_PIPE)
	{
		close(curr->pipe.p[1]);
		*st->pending = curr;
	}
}

static void	process_tok(t_tok *curr, t_minish *shell, int piped,
		t_pipe_state *st)
{
	pid_t	pid;

	if (curr->fd_out != 1 && curr->fd_out != -1)
		st->fd_out = curr->fd_out;
	if (curr->fd_in != 0 && curr->fd_in != -1)
		st->fd_in = curr->fd_in;
	if (curr->is_exe == 1)
	{
		*st->has_exe = 1;
		pid = exec_token(curr, shell, piped);
		if (pid > 0)
			*st->last = pid;
		if (*st->pending)
		{
			close((*st->pending)->pipe.p[0]);
			*st->pending = NULL;
		}
	}
	if (curr->type == TOKEN_PIPE || curr->type == TOKEN_EOF)
	{
		handle_boundary(curr, st);
		st->fd_out = 1;
		st->fd_in = 0;
	}
}

pid_t	run_pipeline(t_tok *lexed, t_minish *shell, int piped)
{
	t_tok			*curr;
	t_tok			*pending;
	pid_t			last;
	int				has_exe;
	t_pipe_state	st;

	pending = NULL;
	last = -1;
	has_exe = 0;
	st = (t_pipe_state){&pending, &last, &has_exe, 1, 0};
	curr = lexed;
	while (curr)
	{
		process_tok(curr, shell, piped, &st);
		curr = curr->next;
	}
	if (pending)
		close(pending->pipe.p[0]);
	return (last);
}
