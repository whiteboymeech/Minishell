/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:26:55 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 19:40:14 by adarolla         ###   ########.fr       */
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
		return (ft_strdup("minishell$ "));
	tmp = ft_strjoin(dir, "$ ");
	free(dir);
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin("Jean Moulin & De Gaulle 2000:", tmp);
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
	prompt = build_prompt();
	*ret = readline(prompt);
	free(prompt);
	if (!(*ret))
	{
		if (g_sig != SIGINT)
		{
			write(2, "exit\n", 5);
			g_sig = -1;
			return (0);
		}
		g_sig = -1;
		return (1);
	}
	return (0);
}
