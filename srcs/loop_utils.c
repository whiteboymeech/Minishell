/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:26:55 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/20 17:46:35 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static char	*build_prompt(void)
{
	char	*dir;
	char	*tmp;
	char	*prompt;

	dir = getcwd(NULL, 0);
	if (!dir)
		return (NULL);
	tmp = ft_strjoin(dir, "$ ");
	free(dir);
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
	*ret = readline(prompt);
	free(prompt);
	if (!(*ret))
	{
		//g_sig = 0;
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
