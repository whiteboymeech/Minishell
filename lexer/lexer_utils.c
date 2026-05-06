/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 15:42:49 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 18:11:07 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

t_tok	*new_node(t_type tokens, char *value)
{
	t_tok	*tkns;

	tkns = ft_calloc(1, sizeof(t_tok));
	if (!tkns)
		return (NULL);
	tkns->type = tokens;
	tkns->value = ft_strdup(value);
	if (!tkns->value)
	{
		free(tkns);
		return (NULL);
	}
	tkns->next = NULL;
	tkns->prev = NULL;
	tkns->is_exe = -1;
	tkns->fd_in = 0;
	tkns->fd_out = 1;
	return (tkns);
}

void	add_token_back(t_tok **tok, t_tok *new_element)
{
	t_tok	*tkns;

	if (!new_element)
		return ;
	if (!*tok)
	{
		*tok = new_element;
		return ;
	}
	tkns = *tok;
	while (tkns->next != NULL)
		tkns = tkns->next;
	tkns->next = new_element;
	new_element->prev = tkns;
}

void	free_tokens(t_tok **tokens)
{
	t_tok	*tok;
	t_tok	*current;

	tok = *tokens;
	while (tok)
	{
		current = tok->next;
		free(tok->value);
		free(tok);
		tok = current;
	}
}

int	add_word(char *ret, int i, t_tok **tokens, int start)
{
	char	*value;
	char	quote;

	start = i;
	while (ret[i] && !is_sep(ret[i]))
	{
		if (ret[i] == '\'' || ret[i] == '\"')
		{
			quote = ret[i++];
			while (ret[i] && ret[i] != quote)
				i++;
			if (ret[i])
				i++;
		}
		else
			i++;
	}
	value = ft_substr(ret, start, i - start);
	if (!value)
		return (free_tokens(tokens), 0);
	add_token_back(tokens, new_node(TOKEN_WORD, value));
	free(value);
	return (i);
}

int	skip_spaces(char *ret, int i)
{
	while (ret[i] && (ret[i] == ' ' || ret[i] == '\t'))
		i++;
	return (i);
}
