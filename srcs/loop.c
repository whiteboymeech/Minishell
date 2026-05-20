/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:52:04 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/20 18:05:01 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include "libft.h"

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
		{
			// close(curr->pipe.p[0]);
			close(curr->pipe.p[1]);
		}
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
		{
			close(curr->pipe.p[0]);
			// close(curr->pipe.p[1]);
		}
		curr = curr->next;
	}
}

static int	ft_heredoc_tok_count(t_tok *lexed)
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

static void	sigint_parent_handler(int sig)
{
	write(1, "\n", 1);
	g_sig = sig;
}

void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, "Quit\n", 5);
	}
}


int	parse_pipeline(t_tok *lexed, t_minish *shell)
{
	pid_t	last_pid;
	int		redir_err;
	int		heredoc_err;
	int		child_pid;

	redir_err = open_redir_fds(lexed);
	open_pipes(lexed);
	apply_pipes(lexed);
	apply_redir_fds(lexed);
	heredoc_err = ft_heredoc_tok_count(lexed);
	// signal(SIGINT, SIG_DFL);
	child_pid = fork();
	g_sig = -1;
	signal(SIGINT, sigint_parent_handler);
	if (child_pid == 0)
	{
		signal(SIGINT, sigint_heredoc_handler);
		if (heredoc_err == 0)
			get_heredocs(lexed, shell);
		ft_close_heredocs(lexed);
		close_redir_fds(lexed);
		close_pipe_fds(lexed, 0, 1);
		make_dissapear(shell);
		if (heredoc_err == -1)
			exit(2);
		else
			exit(0);
	}
	if ((redir_err && !has_pipe(lexed)) || heredoc_err == -1)
	{
		shell->exit = 1;
		if (heredoc_err == -1)
			shell->exit = 2;
		close_redir_fds(lexed);
		return (-1);
	}
	wait_children(child_pid, shell);
	ft_close_heredocs_in(lexed);
	shell->envp = env_to_array(shell->env);
	last_pid = -1;
	signal(SIGQUIT, sigquit_handler);
	if (g_sig != SIGINT)
		last_pid = run_pipeline(lexed, shell, has_pipe(lexed));
	else
		g_sig = -1;
	ft_close_heredocs_out(lexed);
	free_argv(shell->envp);
	shell->envp = NULL;
	wait_children(last_pid, shell);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
	if (g_sig == SIGINT)
	{
		shell->exit = 130;
		g_sig = -1;
	}
	close_redir_fds(lexed);
	return (0);
}
