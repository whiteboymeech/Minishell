/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:39:13 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 02:23:02 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	env_unset(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static int	is_valid_unset_id(const char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset(t_tok *tokens, t_minish *shell)
{
	t_tok	*tok;
	char	*eq;
	char	*key;

	tok = tokens->next;
	while (tok && tok->type == TOKEN_WORD)
	{
		key = tok->value;
		eq = ft_strchr(key, '=');
		if (eq)
			*eq = '\0';
		if (!is_valid_unset_id(tok->value))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(tok->value, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (0);
		}
		else
			env_unset(&shell->env, tok->value);
		if (eq)
			*eq = '=';
		tok = tok->next;
	}
	return (0);
}
