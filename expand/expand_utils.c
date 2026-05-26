/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:07:15 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 19:15:43 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*dollar(char *value, int *i, t_minish *shell)
{
	int		start;
	char	*name;
	char	*str;

	(*i)++;
	if (value[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit));
	}
	start = *i;
	while (ft_isdigit(value[*i]) || ft_isalpha(value[*i]) || value[*i] == '_')
		(*i)++;
	if (start == *i)
		return (ft_strdup("$"));
	name = ft_substr(value, start, *i - start);
	if (!name)
		return (NULL);
	str = get_env_val_alloc(shell->env, name);
	free(name);
	if (!str)
		return (ft_strdup(""));
	return (str);
}

static char	*safe_join(char *res, char *piece)
{
	char	*tmp;

	tmp = ft_strjoin(res, piece);
	free(res);
	free(piece);
	return (tmp);
}

int	append_piece(char **res, char *piece)
{
	if (!piece)
		return (0);
	*res = safe_join(*res, piece);
	return (*res != NULL);
}

char	*expand_squote(char *value, int *i)
{
	char	buffer[2];
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	buffer[1] = '\0';
	(*i)++;
	while (value[*i] && value[*i] != '\'')
		normal_copy(value, &res, buffer, i);
	if (value[*i])
		(*i)++;
	return (res);
}

char	*expand_dquote(char *value, int *i, t_minish *shell)
{
	char	buffer[2];
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	buffer[1] = '\0';
	while (value[*i] && value[*i] != '"')
	{
		if (value[*i] != '$')
			normal_copy(value, &res, buffer, i);
		else
		{
			if (!append_piece(&res, dollar(value, i, shell)))
			{
				free(res);
				return (NULL);
			}
		}
	}
	if (value[*i])
		(*i)++;
	return (res);
}
