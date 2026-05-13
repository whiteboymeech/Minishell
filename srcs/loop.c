/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:52:04 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/10 21:03:06 by adarolla         ###   ########.fr       */
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

void	parse_pipeline(t_tok *lexed, t_minish *shell)
{
	pid_t	last_pid;
	int		redir_err;
	int		pipe;

	pipe = 0;
	redir_err = open_redir_fds(lexed);
	open_pipes(lexed);
	apply_pipes(lexed);
	apply_redir_fds(lexed);
	get_heredocs(lexed, shell);
	if (redir_err && !has_pipe(lexed))
	{
		shell->exit = 1;
		close_redir_fds(lexed);
		return ;
	}
	shell->envp = env_to_array(shell->env);
	pipe = has_pipe(lexed);
	last_pid = run_pipeline(lexed, shell, pipe);
	free_argv(shell->envp);
	shell->envp = NULL;
	wait_children(last_pid, shell);
	close_redir_fds(lexed);
}
