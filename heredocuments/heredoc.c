/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:25:35 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/25 17:33:17 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	read_heredoc(t_tok *curr, t_minish *shell, int quoted)
{
	char	*line;
	char	*exp;

	while (g_sig != SIGINT)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, curr->next->value) == 0)
		{
			free(line);
			break ;
		}
		if (quoted)
			exp = ft_strdup(line);
		else
			exp = expand_heredoc_line(line, shell);
		free(line);
		if (!exp)
			break ;
		write(curr->pipe.p[1], exp, ft_strlen(exp));
		write(curr->pipe.p[1], "\n", 1);
		free(exp);
	}
	close(curr->pipe.p[1]);
}

char	*r_quotes(char *data)
{
	int		i;
	int		j;
	char	*str;
	char	quote;

	i = 0;
	quote = 0;
	j = 0;
	str = ft_calloc((ft_strlen(data) + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (data[i])
	{
		if ((data[i] == '\'' || data[i] == '\"') && quote == 0)
			quote = data[i];
		else if (data[i] == quote)
			quote = 0;
		else
			str[j++] = data[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

void	get_heredocs(t_tok *lexed, t_minish *shell)
{
	t_tok	*curr;
	char	*del;

	curr = lexed;
	del = NULL;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC && curr->next
			&& curr->next->type == TOKEN_WORD)
			read_heredoc(curr, shell, curr->heredoc_quoted);
		curr = curr->next;
	}
}
