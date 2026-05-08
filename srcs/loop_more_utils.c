/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_more_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:30:11 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/08 19:11:26 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	has_pipe(t_tok *lexed)
{
	t_tok	*curr;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_PIPE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

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
		setup_fds(ctx);
		close_pipe_fds(ctx->tokens, ctx->fd_in, ctx->fd_out);
		curr->fd_out = 1;
		curr->fd_in = 0;
		result = run(curr, shell);
		free_tokens(&shell->tokens);
		free_argv(shell->envp);
		free_argv(shell->paths);
		free_env(shell->env);
		exit(result);
	}
	return (pid);
}

pid_t	exec_token(t_tok *curr, t_minish *shell, int piped)
{
	pid_t		pid;
	int			result;
	t_exec_ctx	ctx;

	result = -1;
	pid = 0;
	if (!piped)
		result = run(curr, shell);
	if (result != -1)
	{
		shell->exit = result;
		return (-2);
	}
	ctx = (t_exec_ctx){shell->envp, curr->fd_out, curr->fd_in, shell->tokens};
	if (piped && is_builtin(curr))
		return (fork_build(curr, shell, &ctx));
	pid = ft_exec_if_found(curr, shell->paths, &ctx);
	if (pid < 0)
		shell->exit = 127;
	return (pid);
}
