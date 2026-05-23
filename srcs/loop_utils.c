/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:26:55 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/22 00:29:11 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static char	*build_prompt(void)
{
	char	dir[4096];
	char	*tmp;
	char	*prompt;

	if (getcwd(dir, 4096) == NULL)
		return (NULL);
	tmp = ft_strjoin(dir, "$ ");
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
		return (0);
	*ret = readline(prompt);
	free(prompt);
	if (!(*ret))
	{
		// g_sig = 0;
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
