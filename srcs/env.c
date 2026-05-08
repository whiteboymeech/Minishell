/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d43.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2027/03/30 02:30:06 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/08 00:00:45 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	insert_node(t_env **env, t_env **tail, t_env *node)
{
	if (!*env)
	{
		*env = node;
		*tail = node;
		return ;
	}
	(*tail)->next = node;
	*tail = node;
}

t_env	*build_env(char **envp)
{
	t_env	*env;
	t_env	*node;
	t_env	*tail;
	int		i;

	env = (t_env *){0};
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		node = create_node(envp[i]);
		if (!node)
			return (env);
		insert_node(&env, &tail, node);
		i++;
	}
	return (env);
}

t_env	*make_env_node(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if(value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!new->key || (value && !new->value))
	{
		free(new->key);
		free(new->value);
		free(new);
		return (NULL);
	}
	return (new);
}

void	add_env(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*new;

	node = find_env(*env, key);
	if (node)
	{
		free(node->value);
		if (value)
			node->value = ft_strdup(value);
		else
			node->value = NULL;
		return ;
	}
	new = make_env_node(key, value);
	if (!new)
		return ;
	append_env(env, new);
}

int	env(t_minish *shell, t_tok *tokens)
{
	t_env	*curr;

	if (tokens->next && tokens->next->type != TOKEN_EOF
		&& tokens->next->type == TOKEN_WORD)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(tokens->next->value, 2);
		ft_putendl_fd("': No such file or directory", 2);
		return (127);
	}
	curr = shell->env;
	while (curr)
	{
		if (curr->value != NULL) {
			ft_putstr_fd(curr->key, 1);
			ft_putstr_fd("=", 1);
			if(curr->value)
				ft_putendl_fd(curr->value, 1);
			else
				write(1, "\n", 1);
		}
		curr = curr->next;
	}
	return (0);
}
