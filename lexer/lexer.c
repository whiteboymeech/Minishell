/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d43.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2027/03/12 02:15:41 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 19:06:30 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*show_type(t_tok *tokens)
{
	if (tokens->type == TOKEN_PIPE)
		return (MAGENTA "TOKEN_PIPE" RESET);
	if (tokens->type == TOKEN_REDIR_IN)
		return (BLUE "TOKEN_REDIR_IN" RESET);
	if (tokens->type == TOKEN_REDIR_OUT)
		return (BLUE "TOKEN_REDIR_OUT" RESET);
	if (tokens->type == TOKEN_EOF)
		return (RED "TOKEN_EOF" RESET);
	if (tokens->type == TOKEN_WORD)
		return (GREEN "TOKEN_WORD" RESET);
	if (tokens->type == TOKEN_APPEND)
		return (YELLOW "TOKEN_APPEND" RESET);
	if (tokens->type == TOKEN_HEREDOC)
		return (CYAN "TOKEN_HEREDOC" RESET);
	return ("UNKNOWN");
}

void	print_lexer(t_tok *tokens)
{
	while (tokens)
	{
		printf(CYAN "[value]" RESET " = [" GREEN "%s" RESET "]\n",
			tokens->value);
		printf(CYAN "[type]" RESET "  = [%s]\n", show_type(tokens));
		if (tokens->type != TOKEN_EOF)
			printf(MAGENTA "/==========\\\n" RESET);
		tokens = tokens->next;
	}
}

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

	i = 0;
	tokens = NULL;
	while (ret[i])
	{
		i = skip_spaces(ret, i);
		if (!ret[i])
			break ;
		if (!lexer_step(ret, &i, &tokens))
			return (NULL);
	}
	add_token_back(&tokens, new_node(TOKEN_EOF, ""));
	print_lexer(tokens);
	return (tokens);
}
