/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_launch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenois <marvin@43.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 23:31:15 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/23 23:18:39 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include <signal.h>

void	setup_fds(t_exec_ctx *ctx)
{
	if (ctx->fd_in == -1 || ctx->fd_out == -1)
		exit(1);
	if (ctx->fd_out != 1)
	{
		dup2(ctx->fd_out, 1);
		close(ctx->fd_out);
	}
	if (ctx->fd_in != 0)
	{
		dup2(ctx->fd_in, 0);
		close(ctx->fd_in);
	}
}

static void	handle_execve_error(t_tok *lex, char *path, int err)
{
	struct stat	st;

	if (err == EACCES && stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
	else if (err == ENOENT)
	{
		ft_putstr_fd(lex->value, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (err == EACCES)
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	else
	{
		ft_putstr_fd(lex->value, 2);
		ft_putendl_fd(": execve failed", 2);
	}
}

static void	exec_child(t_tok *lex, char *path, char **argv, t_exec_ctx *ctx)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	if (ctx->fd_in == -1 || ctx->fd_out == -1)
	{
		close_pipe_fds(ctx->tokens, 0, 1);
		close_redir_fds(ctx->tokens);
		free(path);
		free(argv);
		make_dissapear(ctx->shell);
		exit(1);
	}
	setup_fds(ctx);
	close_pipe_fds(ctx->tokens, ctx->fd_in, ctx->fd_out);
	close_redir_fds(ctx->tokens);
	execve(path, argv, ctx->envp);
	handle_execve_error(lex, path, errno);
	free(path);
	free(argv);
	make_dissapear(ctx->shell);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

static pid_t	exec_not_found(t_tok *lex, t_exec_ctx *ctx)
{
	pid_t	child_pid;

	ft_putstr_fd(lex->value, 2);
	ft_putendl_fd(": command not found", 2);
	child_pid = fork();
	if (child_pid != 0)
		return (child_pid);
	if (ctx->fd_in == -1 || ctx->fd_out == -1)
	{
		close_pipe_fds(ctx->tokens, 0, 1);
		close_redir_fds(ctx->tokens);
		make_dissapear(ctx->shell);
		exit(1);
	}
	setup_fds(ctx);
	close_pipe_fds(ctx->tokens, ctx->fd_in, ctx->fd_out);
	close_redir_fds(ctx->tokens);
	make_dissapear(ctx->shell);
	exit(127);
}

pid_t	ft_exec_if_found(t_tok *lex, char **paths, t_exec_ctx *ctx)
{
	char	*path_exe;
	char	**exe_argv;
	pid_t	child_pid;

	if (lex->type == TOKEN_EOF)
		return (-1);
	path_exe = word_is_exe(lex->value, paths);
	if (!path_exe)
		return (exec_not_found(lex, ctx));
	exe_argv = ft_build_exe_argv(lex);
	if (!exe_argv)
	{
		free(path_exe);
		return (-1);
	}
	child_pid = fork();
	if (child_pid == 0)
		exec_child(lex, path_exe, exe_argv, ctx);
	free(exe_argv);
	free(path_exe);
	return (child_pid);
}
