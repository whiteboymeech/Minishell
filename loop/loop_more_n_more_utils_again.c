/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_more_n_more_utils_again.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:03:57 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/25 16:16:48 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

pid_t	exec_empty_segment(int fd_out, int fd_in, t_minish *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd_out != 1)
		{
			dup2(fd_out, 1);
			close(fd_out);
		}
		if (fd_in != 0)
		{
			dup2(fd_in, 0);
			close(fd_in);
		}
		close_pipe_fds(shell->tokens, fd_in, fd_out);
		close_redir_fds(shell->tokens);
		make_dissapear(shell);
		exit(0);
	}
	return (pid);
}

void	ft_close_heredocs(t_tok *lexed)
{
	t_tok	*curr;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC)
		{
			close(curr->pipe.p[0]);
			close(curr->pipe.p[1]);
		}
		curr = curr->next;
	}
}

void	ft_close_heredocs_in(t_tok *lexed)
{
	t_tok	*curr;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC)
			close(curr->pipe.p[1]);
		curr = curr->next;
	}
}

void	ft_close_heredocs_out(t_tok *lexed)
{
	t_tok	*curr;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC)
			close(curr->pipe.p[0]);
		curr = curr->next;
	}
}

int	ft_heredoc_tok_count(t_tok *lexed)
{
	int		i;
	t_tok	*curr;

	curr = lexed;
	i = 0;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC)
			i++;
		curr = curr->next;
	}
	if (i > 16)
	{
		ft_close_heredocs(lexed);
		ft_putstr_fd("minishell: maximum here-document count exceeded\n",
			curr->prev->fd_out);
		return (-1);
	}
	return (0);
}
