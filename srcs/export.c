/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:08:37 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/13 19:14:19 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static char	*get_export_key(char *arg, char *eq, int *append)
{
	*append = 0;
	if (eq && eq > arg && *(eq - 1) == '+')
	{
		*append = 1;
		return (ft_substr(arg, 0, eq - arg - 1));
	}
	if (eq)
		return (ft_substr(arg, 0, eq - arg));
	return (ft_strdup(arg));
}

static char	*apply_append(t_env **env, char *key, char *value)
{
	char	*old;
	char	*result;

	old = get_env_value(*env, key);
	if (!old)
		old = "";
	result = ft_strjoin(old, value);
	free(value);
	return (result);
}

static int	export_set(t_minish *ev, char *key, char *eq, int append)
{
	char	*value;

	value = ft_strdup(eq + 1);
	if (!value)
		return (1);
	if (append)
	{
		value = apply_append(&ev->env, key, value);
		if (!value)
			return (1);
	}
	add_env(&ev->env, key, value);
	free(value);
	return (0);
}

int	export_one(t_minish *ev, char *arg)
{
	char	*eq;
	char	*key;
	char	*exist;
	int		append;
	int		ret;

	eq = ft_strchr(arg, '=');
	key = get_export_key(arg, eq, &append);
	if (!key || !is_valid_identifier(key))
	{
		ft_putendl_fd("export: not a valid identifier", 2);
		free(key);
		return (1);
	}
	if (!eq)
	{
		exist = get_env_value(ev->env, key);
		if (!exist)
			add_env(&ev->env, key, NULL);
		free(key);
		return (0);
	}
	ret = export_set(ev, key, eq, append);
	free(key);
	return (ret);
}

int	export(t_minish *ev, t_tok *tokens)
{
	t_tok	*curr;
	int		ret;

	curr = tokens->next;
	while (curr && curr->type != TOKEN_EOF
		&& curr->type != TOKEN_WORD && curr->type != TOKEN_PIPE)
		curr = curr->next;
	if (!curr || curr->type == TOKEN_EOF || curr->type == TOKEN_PIPE)
	{
		print_env(ev->env);
		return (0);
	}
	ret = 0;
	while (curr && curr->type == TOKEN_WORD)
	{
		if (curr->value[0] == '=')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(curr->value, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
 		}
		else if (export_one(ev, curr->value) != 0)
			ret = 1;
		curr = curr->next;
	}
	return (ret);
}
