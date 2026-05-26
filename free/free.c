/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:02:56 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/09 03:37:24 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	make_dissapear(t_minish *shell)
{
	if (shell->tokens)
		free_lexed(shell->tokens);
	if (shell->env)
		free_env(shell->env);
	if (shell->paths)
		free_argv(shell->paths);
	if (shell->envp)
		free_argv(shell->envp);
	rl_clear_history();
}

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
