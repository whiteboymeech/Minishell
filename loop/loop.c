/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:52:04 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/23 23:25:10 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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

static void	heredoc_child(t_tok *lexed, t_minish *shell, int heredoc_err)
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

static void	run_and_wait(t_tok *lexed, t_minish *shell, int child_pid)
{
	pid_t	last_pid;

	wait_children(child_pid, shell);
	ft_close_heredocs_in(lexed);
	shell->envp = env_to_array(shell->env);
	last_pid = -1;
	signal(SIGQUIT, sigquit_handler);
	if (g_sig != SIGINT)
		last_pid = run_pipeline(lexed, shell, has_pipe(lexed));
	else
		g_sig = -1;
	close_pipe_fds(lexed, 0, 1);
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
}

int	parse_pipeline(t_tok *lexed, t_minish *shell)
{
	int	redir_err;
	int	heredoc_err;
	int	child_pid;

	redir_err = open_redir_fds(lexed);
	open_pipes(lexed);
	apply_pipes(lexed);
	apply_redir_fds(lexed);
	heredoc_err = ft_heredoc_tok_count(lexed);
	child_pid = fork();
	g_sig = -1;
	signal(SIGINT, sigint_parent_handler);
	if (child_pid == 0)
		heredoc_child(lexed, shell, heredoc_err);
	if ((redir_err && !has_pipe(lexed)) || heredoc_err == -1)
	{
		shell->exit = 1 + (heredoc_err == -1);
		waitpid(child_pid, NULL, 0);
		close_pipe_fds(lexed, 0, 1);
		close_redir_fds(lexed);
		return (0);
	}
	run_and_wait(lexed, shell, child_pid);
	return (0);
}
