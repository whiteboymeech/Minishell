/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 19:56:33 by mabenois          #+#    #+#             */
/*   Updated: 2026/05/04 19:22:36 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (paths);
}

char	**get_paths_from_env(t_env *env)
{
	char	*path_val;

	path_val = get_env_value(env, "PATH");
	if (!path_val || path_val[0] == '\0')
		return (NULL);
	return (ft_split(path_val, ':'));
}

static char	*search_in_paths(char *word, char **paths)
{
	int			i;
	char		*tmp;
	struct stat	st;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_calloc(1, ft_strlen(paths[i]) + ft_strlen(word) + 2);
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(tmp, "/", ft_strlen(tmp) + 2);
		ft_strlcat(tmp, word, ft_strlen(tmp) + ft_strlen(word) + 1);
		if (access(tmp, X_OK) == 0 && stat(tmp, &st) == 0
			&& S_ISREG(st.st_mode))
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}

char	*word_is_exe(char *word, char **paths)
{
	static char	*dot_path[] = {".", NULL};
	struct stat	st;

	if (!word)
		return (NULL);
	if (word[0] == '/' || (word[0] == '.' && word[1] == '/'))
	{
		if (stat(word, &st) != 0)
			return (NULL);
		if (S_ISREG(st.st_mode))
			return (ft_strdup(word));
		if (access(word, X_OK) != 0)
			return (ft_strdup(word));
		return (ft_strdup(word));
	}
	if (!paths)
		return (search_in_paths(word, dot_path));
	return (search_in_paths(word, paths));
}
