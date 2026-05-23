/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_more_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:30:11 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/23 22:51:34 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	wait_children(pid_t last_pid, t_minish *shell)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit = 128 + WTERMSIG(status);
		}
	}
}

int	is_builtin(t_tok *tok)
{
	if (!tok || !tok->value)
		return (0);
	return (!ft_strcmp(tok->value, "echo") || !ft_strcmp(tok->value, "pwd")
		|| !ft_strcmp(tok->value, "cd") || !ft_strcmp(tok->value, "env")
		|| !ft_strcmp(tok->value, "export") || !ft_strcmp(tok->value, "unset")
		|| !ft_strcmp(tok->value, "exit"));
}

pid_t	fork_build(t_tok *curr, t_minish *shell, t_exec_ctx *ctx)
{
	int		result;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
		setup_fds(ctx);
		close_pipe_fds(ctx->tokens, ctx->fd_in, ctx->fd_out);
		close_redir_fds(ctx->tokens);
		curr->fd_out = 1;
		curr->fd_in = 0;
		result = run(curr, shell);
		make_dissapear(shell);
		exit(result);
	}
	return (pid);
}

static int	run_builtin_unpiped(t_tok *curr, t_minish *shell)
{
	int	sv_out;
	int	sv_in;
	int	result;

	if (!ft_strcmp(curr->value, "exit"))
		return (run(curr, shell));
	sv_out = dup(STDOUT_FILENO);
	sv_in = dup(STDIN_FILENO);
	if (curr->fd_out != -1 && curr->fd_out != STDOUT_FILENO)
		dup2(curr->fd_out, STDOUT_FILENO);
	if (curr->fd_in != -1 && curr->fd_in != STDIN_FILENO)
		dup2(curr->fd_in, STDIN_FILENO);
	result = run(curr, shell);
	dup2(sv_out, STDOUT_FILENO);
	dup2(sv_in, STDIN_FILENO);
	close(sv_out);
	close(sv_in);
	if (result != -1)
	{
		if (curr->fd_out != -1 && curr->fd_out != STDOUT_FILENO)
			close(curr->fd_out);
		if (curr->fd_in != -1 && curr->fd_in != STDIN_FILENO)
			close(curr->fd_in);
	}
	return (result);
}

pid_t	exec_token(t_tok *curr, t_minish *shell, int piped)
{
	t_exec_ctx	ctx;
	int			result;
	pid_t		pid;

	result = -1;
	if (!piped)
		result = run_builtin_unpiped(curr, shell);
	if (result != -1)
	{
		shell->exit = result;
		return (-2);
	}
	ctx = (t_exec_ctx){shell->envp, curr->fd_out, curr->fd_in, shell->tokens,
		shell};
	if (piped && is_builtin(curr))
		return (fork_build(curr, shell, &ctx));
	pid = ft_exec_if_found(curr, shell->paths, &ctx);
	if (pid < 0)
		shell->exit = 127;
	return (pid);
}
