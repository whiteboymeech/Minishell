/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:16:49 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 23:11:18 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include <readline/readline.h>

static void	read_heredoc(t_tok *curr)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, curr->next->value) == 0)
		{
			free(line);
			break ;
		}
		write(curr->pipe.p[1], line, ft_strlen(line));
		write(curr->pipe.p[1], "\n", 1);
		free(line);
	}
	close(curr->pipe.p[1]);
}

void	get_heredocs(t_tok *lexed)
{
	t_tok	*curr;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC && curr->next
			&& curr->next->type == TOKEN_WORD)
			read_heredoc(curr);
		curr = curr->next;
	}
}
