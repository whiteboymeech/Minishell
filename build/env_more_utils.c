/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_more_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 14:36:37 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 14:55:29 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

t_env	*find_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_env(t_env *env, int fd_out)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", fd_out);
		ft_putstr_fd(env->key, fd_out);
		if (env->value)
		{
			ft_putstr_fd("=\"", fd_out);
			ft_putstr_fd(env->value, fd_out);
			ft_putstr_fd("\"", fd_out);
		}
		write(fd_out, "\n", 1);
		env = env->next;
	}
}
