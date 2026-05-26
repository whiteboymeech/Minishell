/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_more_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:28:00 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/25 17:38:32 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	skip_spaces(char *ret, int i)
{
	while (ret[i] && (ret[i] == ' ' || ret[i] == '\t'))
		i++;
	return (i);
}

static int	add_redir_in(char *ret, int *i, t_tok **tokens)
{
	t_tok	*node;
	int		j;

	if (ret[*i + 1] == '<')
	{
		node = new_node(TOKEN_HEREDOC, "<<");
		(*i) += 2;
		j = *i;
		while (ret[j] == ' ' || ret[j] == '\t')
			j++;
		if (ret[j] == '\'' || ret[j] == '"')
			node->heredoc_quoted = 1;
		else
			node->heredoc_quoted = 0;
		add_token_back(tokens, node);
		return (1);
	}
	add_token_back(tokens, new_node(TOKEN_REDIR_IN, "<"));
	(*i)++;
	return (1);
}

static int	add_redir_out(char *ret, int *i, t_tok **tokens)
{
	if (ret[*i + 1] == '>')
	{
		add_token_back(tokens, new_node(TOKEN_APPEND, ">>"));
		(*i) += 2;
		return (1);
	}
	add_token_back(tokens, new_node(TOKEN_REDIR_OUT, ">"));
	(*i)++;
	return (1);
}

int	add_token(char *ret, int *i, t_tok **tokens)
{
	if (ret[*i] == '|')
	{
		add_token_back(tokens, new_node(TOKEN_PIPE, "|"));
		(*i)++;
		return (1);
	}
	if (ret[*i] == '<')
		return (add_redir_in(ret, i, tokens));
	if (ret[*i] == '>')
		return (add_redir_out(ret, i, tokens));
	return (0);
}
