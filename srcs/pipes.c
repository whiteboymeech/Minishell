/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:34:14 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/07 18:23:27 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	open_pipes(t_tok *lexed)
{
	t_tok	*curr;

	curr = lexed;
	while (curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_PIPE || curr->type == TOKEN_HEREDOC)
		{
			if (pipe(curr->pipe.p) == -1)
				return ;
		}
		curr = curr->next;
	}
}

void	apply_pipes(t_tok *lexed)
{
	t_tok	*curr;
	t_tok	*curr2;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_PIPE)
		{
			curr2 = curr->next;
			while (curr2 && curr2->type != TOKEN_PIPE
				&& curr2->type != TOKEN_EOF && curr2->is_exe != 1)
				curr2 = curr2->next;
			if (curr2 && curr2->is_exe == 1)
				curr2->fd_in = curr->pipe.p[0];
			curr2 = curr;
			while (curr2->prev && curr2->is_exe != 1)
				curr2 = curr2->prev;
			if (curr2->is_exe == 1)
				curr2->fd_out = curr->pipe.p[1];
		}
		curr = curr->next;
	}
}
