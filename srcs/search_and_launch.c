/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_launch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenois <marvin@43.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 23:31:15 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 22:24:01 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	setup_fds(t_exec_ctx *ctx)
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
	setup_fds(ctx);
	execve(path, argv, ctx->envp);
	if (errno == EACCES)
	{
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	ft_putstr_fd(lex->value, 2);
	ft_putendl_fd(": execve failed", 2);
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
		return (-1);
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

void	free_lexed(t_tok *lex)
{
	t_tok	*curr;
	t_tok	*last;

	curr = lex;
	last = curr;
	while (curr)
	{
		curr = curr->next;
		free(last->value);
		free(last);
		last = curr;
	}
}
