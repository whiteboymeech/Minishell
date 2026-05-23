/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:25:35 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/23 23:00:45 by adarolla         ###   ########.fr       */
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

void	get_heredocs(t_tok *lexed, t_minish *shell)
{
	t_tok	*curr;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC && curr->next
			&& curr->next->type == TOKEN_WORD)
			read_heredoc(curr, shell, curr->heredoc_quoted);
		curr = curr->next;
	}
}
