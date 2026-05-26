/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 03:37:26 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/09 03:38:26 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_redir_fds(t_tok *lexed)
{
	t_tok	*curr;
	int		fd_out;
	int		fd_in;

	curr = lexed;
	fd_out = -1;
	fd_in = -1;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->fd_out != 1 && curr->fd_out != fd_out && curr->fd_out != -1)
		{
			fd_out = curr->fd_out;
			close(curr->fd_out);
		}
		if (curr->fd_in != 0 && curr->fd_in != fd_in && curr->fd_in != -1)
		{
			fd_in = curr->fd_in;
			close(curr->fd_in);
		}
		curr = curr->next;
	}
}

void	close_pipe_fds(t_tok *tokens, int keep_in, int keep_out)
{
	t_tok	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE || curr->type == TOKEN_HEREDOC)
		{
			if (curr->pipe.p[0] != keep_in && curr->pipe.p[0] != keep_out)
				close(curr->pipe.p[0]);
			if (curr->pipe.p[1] != keep_in && curr->pipe.p[1] != keep_out)
				close(curr->pipe.p[1]);
		}
		curr = curr->next;
	}
}
