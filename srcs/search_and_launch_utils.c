/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_and_launch_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:00:41 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/04 19:19:12 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	is_redir_target(t_tok *tok)
{
	if (!tok->prev)
		return (0);
	return (tok->prev->type == TOKEN_REDIR_IN
		|| tok->prev->type == TOKEN_REDIR_OUT || tok->prev->type == TOKEN_APPEND
		|| tok->prev->type == TOKEN_HEREDOC);
}

char	**ft_build_exe_argv(t_tok *lex)
{
	t_tok	*curr;
	char	**exe_av;
	size_t	size;

	curr = lex;
	size = 0;
	while (curr && curr->type != TOKEN_PIPE && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_WORD && !is_redir_target(curr))
			size++;
		curr = curr->next;
	}
	exe_av = ft_calloc(sizeof(char *), size + 1);
	if (!exe_av)
		return (NULL);
	curr = lex;
	size = 0;
	while (curr && curr->type != TOKEN_PIPE && curr->type != TOKEN_EOF)
	{
		if (curr->type == TOKEN_WORD && !is_redir_target(curr))
			exe_av[size++] = curr->value;
		curr = curr->next;
	}
	exe_av[size] = NULL;
	return (exe_av);
}
