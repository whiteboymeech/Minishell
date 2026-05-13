/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:11:39 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/10 22:07:02 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	dot(void)
{
	ft_putendl_fd(".: filename argument required", 2);
	ft_putendl_fd(".: usage: . filename [arguments]", 2);
	return (2);
}

int	run(t_tok *tokens, t_minish *shell)
{
	t_tok	*tok;

	tok = tokens;
	if (!ft_strcmp(tok->value, "echo"))
		return (echo(tok->next));
	if (!ft_strcmp(tok->value, "pwd"))
		return (pwd(tok->next));
	if (!ft_strcmp(tok->value, "cd"))
		return (cd(tokens, shell));
	if (!ft_strcmp(tokens->value, "."))
		return (dot());
	if (!ft_strcmp(tok->value, "env"))
		return (env(shell, tokens));
	if (!ft_strcmp(tok->value, "export"))
		return (export(shell, tokens));
	if (!ft_strcmp(tok->value, "unset"))
		return (unset(tokens, shell));
	if (!ft_strcmp(tok->value, "exit"))
		return (ft_exit(tokens, shell));
	return (-1);
}
