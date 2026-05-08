/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 02:16:49 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 19:26:39 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static char	*read_heredoc_line_interactive(void)
{
	return (readline("> "));
}

static char	*read_heredoc_line_fd(void)
{
	char	buf[4096];
	int		i;
	char	c;
	int		r;

	i = 0;
	while (i < 4095)
	{
		r = read(0, &c, 1);
		if (r <= 0)
		{
			if (i == 0)
				return (NULL);
			break ;
		}
		if (c == '\n')
			break ;
		buf[i++] = c;
	}
	buf[i] = '\0';
	return (ft_strdup(buf));
}

static void	read_heredoc(t_tok *curr)
{
	char	*line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = read_heredoc_line_interactive();
		else
			line = read_heredoc_line_fd();
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

static t_tok	*find_content_tok(t_tok *heredoc_tok)
{
	t_tok	*curr;
	t_tok	*last_word;

	if (!heredoc_tok->next)
		return (NULL);
	curr = heredoc_tok->next->next;
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

void	get_heredocs(t_tok *lexed)
{
	t_tok	*curr;
	t_tok	*content_tok;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_HEREDOC && curr->next
			&& curr->next->type == TOKEN_WORD)
		{
			content_tok = find_content_tok(curr);
			if (content_tok)
			{
				write_from_token(curr, content_tok);
				content_tok->type = TOKEN_ERROR;
			}
			else
				read_heredoc(curr);
		}
		curr = curr->next;
	}
}
