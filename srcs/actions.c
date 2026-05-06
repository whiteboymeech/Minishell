/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 01:10:59 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 19:25:09 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include "../minishell.h"

t_action	*new_action(t_action_type type, t_tok *lex)
{
	t_action	*new;

	new = ft_calloc(1, sizeof(t_action));
	if (!new)
		return (NULL);
	new->fd_out = 1;
	new->type = type;
	new->lex = lex;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	push_action(t_action **actions, t_action_type type, t_tok *lex)
{
	t_action	*curr;
	t_action	*new;

	new = new_action(type, lex);
	new->fd_out = lex->fd_out;
	new->fd_in = lex->fd_in;
	if (!(*actions))
	{
		*actions = new;
		return ;
	}
	curr = *actions;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
}
