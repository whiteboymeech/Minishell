/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d43.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2027/04/05 15:58:35 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/08 23:15:37 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	append_env(t_env **env, t_env *new)
{
	t_env	*node;

	if (!*env)
	{
		*env = new;
		return ;
	}
	node = *env;
	while (node->next)
		node = node->next;
	node->next = new;
}

t_env	*create_node(char *data)
{
	t_env	*node;
	char	*eq;

	eq = ft_strchr(data, '=');
	if (!eq)
		return (NULL);
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	node->value = ft_strdup(eq + 1);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->key = ft_substr(data, 0, eq - data);
	if (!node->key)
	{
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}

static int	env_count(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

static char	*make_env_str(t_env *env)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, env->value);
	free(tmp);
	return (result);
}

char	**env_to_array(t_env *env)
{
	char	**arr;
	int		i;

	arr = ft_calloc(env_count(env) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i] = make_env_str(env);
		if (!arr[i])
		{
			free_argv(arr);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
