/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d43.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2027/03/12 02:15:41 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/07 18:36:03 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	is_sep(char c)
{
	return (c == '>' || c == '<' || c == '|' || c == '\t' || c == ' ');
}

static int	lexer_step(char *ret, int *i, t_tok **tokens)
{
	if (ret[*i] == '>' || ret[*i] == '<' || ret[*i] == '|')
	{
		if (add_token(ret, i, tokens) == 0)
			return (0);
	}
	else
	{
		*i = add_word(ret, *i, tokens, 0);
		if (*i == 0)
			return (0);
	}
	return (1);
}

t_tok	*lexer(char *ret)
{
	int		i;
	t_tok	*tokens;
	char	*eof;

	i = 0;
	tokens = NULL;
	eof = "";
	while (ret[i])
	{
		i = skip_spaces(ret, i);
		if (!ret[i])
			break ;
		if (!lexer_step(ret, &i, &tokens))
			return (NULL);
	}
	add_token_back(&tokens, new_node(TOKEN_EOF, eof));
	return (tokens);
}
