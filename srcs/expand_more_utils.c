/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_more_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:18:59 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 16:33:07 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	normal_copy(char *value, char **res, char *buffer, int *i)
{
	char	*tmp;

	buffer[0] = value[(*i)++];
	tmp = ft_strjoin(*res, buffer);
	if (!tmp)
		return ;
	free(*res);
	*res = tmp;
}

static int	expand_dollar(char *value, int *i, char **res, t_minish *shell)
{
	if (value[*i + 1] == '\'')
	{
		(*i)++;
		return (append_piece(res, expand_squote(value, i)));
	}
	if (value[*i + 1] == '"')
	{
		(*i) += 2;
		return (append_piece(res, expand_dquote(value, i, shell)));
	}
	return (append_piece(res, dollar(value, i, shell)));
}

static int	expand_one(char *value, int *i, char **res, t_minish *shell)
{
	char	buffer[2];

	buffer[1] = '\0';
	if (value[*i] == '\'')
		return (append_piece(res, expand_squote(value, i)));
	if (value[*i] == '"')
	{
		(*i)++;
		return (append_piece(res, expand_dquote(value, i, shell)));
	}
	if (value[*i] == '$')
		return (expand_dollar(value, i, res, shell));
	normal_copy(value, res, buffer, i);
	return (1);
}

char	*expand(char *value, t_minish *shell)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (value[i])
	{
		if (!expand_one(value, &i, &res, shell))
		{
			free(res);
			return (NULL);
		}
	}
	return (res);
}
