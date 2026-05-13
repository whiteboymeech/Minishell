/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_launch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenois <marvin@43.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 23:31:15 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/11 17:40:55 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

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

static void	exec_child(t_tok *lex, char *path, char **argv, t_exec_ctx *ctx)
{
	struct stat	st;
	int			err;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	setup_fds(ctx);
	close_pipe_fds(ctx->tokens, ctx->fd_in, ctx->fd_out);
	close_redir_fds(ctx->tokens);
	execve(path, argv, ctx->envp);
	err = errno;
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
	free(path);
	free(argv);
	make_dissapear(ctx->shell);
	if (err == EACCES)
		exit(126);
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
	{
		ft_putstr_fd(lex->value, 2);
		ft_putendl_fd(": command not found", 2);
		child_pid = fork();
		if (child_pid == 0)
		{
			setup_fds(ctx);
			close_pipe_fds(ctx->tokens, ctx->fd_in, ctx->fd_out);
			close_redir_fds(ctx->tokens);
			make_dissapear(ctx->shell);
			exit(127);
		}
		return (child_pid);
	}
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
