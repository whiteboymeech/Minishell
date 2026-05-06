/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:28:57 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 18:42:39 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	bad_pipe(t_tok *curr, t_minish *shell)
{
	if (curr->type != TOKEN_PIPE)
		return (0);
	if (curr->next && curr->next->type != TOKEN_PIPE
		&& curr->next->type != TOKEN_EOF)
		return (0);
	ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
	shell->exit = 2;
	return (1);
}

static int	bad_redir(t_tok *curr, t_minish *shell)
{
	if (curr->type != TOKEN_REDIR_IN && curr->type != TOKEN_REDIR_OUT
		&& curr->type != TOKEN_APPEND && curr->type != TOKEN_HEREDOC)
		return (0);
	if (curr->next && curr->next->type == TOKEN_WORD)
		return (0);
	ft_putendl_fd("minishell: syntax error near unexpected token", 2);
	shell->exit = 2;
	return (1);
}

int	validate_syntax(t_tok *lexed, t_minish *shell)
{
	t_tok	*curr;

	curr = lexed;
	if (!curr || curr->type == TOKEN_EOF)
		return (0);
	if (curr->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		shell->exit = 2;
		return (1);
	}
	while (curr && curr->type != TOKEN_EOF)
	{
		if (bad_pipe(curr, shell) || bad_redir(curr, shell))
			return (1);
		curr = curr->next;
	}
	return (0);
}
