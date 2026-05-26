/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_more_more_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:29:39 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/09 03:39:38 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_tok	*new_word_tok(char *value)
{
	t_tok	*tok;

	tok = ft_calloc(1, sizeof(t_tok));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = TOKEN_WORD;
	tok->prev = NULL;
	tok->next = NULL;
	tok->fd_in = 0;
	tok->fd_out = 1;
	return (tok);
}

static void	link_tok(t_tok **tokens, t_tok **prev, t_tok **last, t_tok *new)
{
	new->prev = *prev;
	new->next = NULL;
	if (*prev)
		(*prev)->next = new;
	else
		*tokens = new;
	*prev = new;
	*last = new;
}

static t_tok	*insert_parts(t_tok **tokens, t_tok *prev, t_tok *next,
		char **parts)
{
	t_tok	*new;
	t_tok	*last;
	int		i;

	last = NULL;
	i = 0;
	while (parts[i])
	{
		new = new_word_tok(parts[i]);
		if (!new)
			break ;
		link_tok(tokens, &prev, &last, new);
		i++;
	}
	if (last)
		last->next = next;
	if (next)
		next->prev = last;
	return (last);
}

static t_tok	*replace_with_split(t_tok **tokens, t_tok *current,
		char **parts)
{
	t_tok	*prev;
	t_tok	*next;
	t_tok	*last;

	prev = current->prev;
	next = current->next;
	free(current->value);
	current->value = NULL;
	free(current);
	current = NULL;
	last = insert_parts(tokens, prev, next, parts);
	free(parts);
	parts = NULL;
	return (last);
}

t_tok	*handle_expand(t_tok **tokens, t_tok *current, t_tok *next, char *exp)
{
	char	**parts;

	if (!has_quotes(current->value) && ft_strchr(exp, ' ')
		&& !ft_strchr(current->value, '='))
	{
		parts = ft_split(exp, ' ');
		free(exp);
		if (parts && parts[0])
			return (replace_with_split(tokens, current, parts));
		free(parts);
		return (next);
	}
	update_token_value(current, exp);
	return (next);
}
