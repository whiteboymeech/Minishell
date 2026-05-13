/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:16:49 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/12 23:02:33 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	read_heredoc(t_tok *curr, t_minish *shell, int quoted)
{
	char	*line;
	char	*exp;

	while (1)
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

/*
static t_tok	*find_content_tok(t_tok *heredoc_tok)
{
	t_tok	*curr;
	t_tok	*last_word;

	if (!heredoc_tok->next)
		return (NULL);
	curr = heredoc_tok->next;
	last_word = NULL;
	while (curr && curr->type == TOKEN_WORD)
	{
		if (curr->value && ft_strnstr(curr->value, "\\n",
				ft_strlen(curr->value)))
			last_word = curr;
		curr = curr->next;
	}
	return (last_word);
}
*/

void	get_heredocs(t_tok *lexed, t_minish *shell)
{
	t_tok	*curr;
	//t_tok	*content_tok;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC && curr->next
			&& curr->next->type == TOKEN_WORD)
		{
			/*
			content_tok = find_content_tok(curr);
			if (content_tok)
			{
				write_from_token(curr, content_tok);
				content_tok->type = TOKEN_ERROR;
			}
			else
			*/
				read_heredoc(curr, shell, curr->heredoc_quoted);

			//}
		}
		curr = curr->next;
	}
}
