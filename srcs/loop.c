/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:52:04 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 20:08:25 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	setup_pipeline(t_tok *lexed)
{
	if (open_redir_fds(lexed))
		return (1);
	open_pipes(lexed);
	apply_pipes(lexed);
	apply_redir_fds(lexed);
	get_heredocs(lexed);
	return (0);
}

pid_t	exec_empty_segment(int fd_out, int fd_in)
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
		exit(0);
	}
	return (pid);
}

void	parse_pipeline(t_tok *lexed, t_minish *shell)
{
	pid_t	last_pid;

	if (setup_pipeline(lexed))
	{
		shell->exit = 1;
		close_redir_fds(lexed);
		return ;
	}
	shell->envp = env_to_array(shell->env);
	last_pid = run_pipeline(lexed, shell, has_pipe(lexed));
	free_argv(shell->envp);
	shell->envp = NULL;
	wait_children(last_pid, shell);
	close_redir_fds(lexed);
}
