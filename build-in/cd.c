/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:25:55 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/14 00:09:24 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*get_oldpwd(t_minish *shell)
{
	char	*path;

	path = get_env_value(shell->env, "OLDPWD");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (NULL);
	}
	else
		ft_putendl_fd(path, 1);
	return (path);
}

char	*get_cd_path(t_tok *arg, t_minish *shell)
{
	char	*path;

	if (!arg || arg->type == TOKEN_EOF)
	{
		path = get_env_value(shell->env, "HOME");
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (path);
	}
	if (arg->next && arg->next->type == TOKEN_WORD)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (NULL);
	}
	return (arg->value);
}

void	update_pwd(t_minish *shell, char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	if (oldpwd)
		add_env(&shell->env, "OLDPWD", oldpwd);
	else
		env_unset(&shell->env, "OLD_PWD");
	add_env(&shell->env, "PWD", cwd);
}

int	cd(t_tok *tokens, t_minish *shell)
{
	char	*path;
	char	*oldpwd;

	oldpwd = get_env_value(shell->env, "PWD");
	path = get_cd_path(tokens->next, shell);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
		return (1);
	}
	update_pwd(shell, oldpwd);
	return (0);
}
