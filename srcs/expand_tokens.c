/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:16:49 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 18:34:54 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static t_tok	*remove_token(t_tok **tokens, t_tok *current, t_tok *next)
{
	if (current->prev)
	{
		current->prev->next = next;
		if (next)
			next->prev = current->prev;
	}
	else
	{
		*tokens = next;
		if (next)
			next->prev = NULL;
	}
	free(current->value);
	free(current);
	return (next);
}

static int	is_redir_tok(t_tok *tok)
{
	if (!tok->prev)
		return (0);
	return (tok->prev->type == TOKEN_REDIR_IN
		|| tok->prev->type == TOKEN_REDIR_OUT || tok->prev->type == TOKEN_APPEND
		|| tok->prev->type == TOKEN_HEREDOC);
}

void	update_token_value(t_tok *current, char *exp)
{
	free(current->value);
	current->value = exp;
}

void	expand_tokens(t_tok **tokens, t_minish *shell)
{
	t_tok	*current;
	t_tok	*next;
	char	*exp;

	current = *tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD)
		{
			exp = expand(current->value, shell);
			if ((!exp || !exp[0]) && current->value[0] != '\''
				&& current->value[0] != '"' && !is_redir_tok(current))
			{
				free(exp);
				current = remove_token(tokens, current, next);
				continue ;
			}
			if (exp)
				next = handle_expand(tokens, current, next, exp);
		}
		current = next;
	}
}
