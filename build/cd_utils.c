/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:28:14 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 14:32:13 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_env_val_alloc(t_env *env, char *key)
{
	char	*value;
	char	*ret;

	value = get_env_value(env, key);
	if (!value)
		return (NULL);
	ret = ft_strdup(value);
	if (!ret)
		return (NULL);
	return (ret);
}
