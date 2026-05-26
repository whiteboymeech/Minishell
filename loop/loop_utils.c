/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:26:55 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/26 18:23:14 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	has_pipe(t_tok *lexed)
{
	t_tok	*curr;

	curr = lexed;
	while (curr && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_PIPE)
			return (1);
		curr = curr->next;
	}
	return (0);
}

char	*build_prompt(void)
{
	char		dir[PATH_MAX];
	static char	ret[PATH_MAX];
	char		*tmp;
	char		*prompt;

	tmp = get_path_str(dir, ret);
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin("Jean Moulin & De Gaulle 200:", tmp);
	free(tmp);
	return (prompt);
}

static int	read_chars(char *buf)
{
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
				return (-1);
			break ;
		}
		if (c == '\n')
			break ;
		buf[i++] = c;
	}
	buf[i] = '\0';
	return (i);
}

static int	read_non_interactive(char **ret)
{
	char	buf[4096];
	int		len;

	len = read_chars(buf);
	if (len == -1)
	{
		*ret = NULL;
		return (0);
	}
	*ret = ft_strdup(buf);
	if (!*ret)
		return (-1);
	return (0);
}

int	ft_read_prompt(char **ret)
{
	char	*prompt;

	if (!isatty(STDIN_FILENO))
		return (read_non_interactive(ret));
	rl_done = 0;
	prompt = build_prompt();
	if (!prompt)
		return (1);
	*ret = readline(prompt);
	free(prompt);
	if (!(*ret))
	{
		write(1, "exit\n", 5);
		return (0);
	}
	if (g_sig == SIGINT)
	{
		g_sig = 0;
		free(*ret);
		*ret = NULL;
		return (1);
	}
	return (0);
}
