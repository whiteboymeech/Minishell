/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:02:56 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/08 18:43:02 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_lexed(t_tok *lex)
{
	t_tok	*curr;
	t_tok	*last;

	curr = lex;
	last = curr;
	while (curr)
	{
		curr = curr->next;
		free(last->value);
		free(last);
		last = curr;
	}
}

void	close_pipe_fds(t_tok *tokens, int keep_in, int keep_out)
{
	t_tok	*curr;

	curr = tokens;
	while (curr)
	{
		if (curr->type == TOKEN_PIPE || curr->type == TOKEN_HEREDOC)
		{
			if (curr->pipe.p[0] != keep_in && curr->pipe.p[0] != keep_out)
				close(curr->pipe.p[0]);
			if (curr->pipe.p[1] != keep_in && curr->pipe.p[1] != keep_out)
				close(curr->pipe.p[1]);
		}
		curr = curr->next;
	}
}

void	free_tokens(t_tok **tokens)
{
	t_tok	*tok;
	t_tok	*current;

	tok = *tokens;
	while (tok)
	{
		current = tok->next;
		free(tok->value);
		free(tok);
		tok = current;
	}
}

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

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}
