/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenois <mabenois@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:25:47 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 19:23:32 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	free_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (env)
	{
		curr = env->next;
		free(curr->key);
		free(curr->value);
		free(env);
		env = curr;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minish	shell;

	(void)av;
	(void)ac;
	shell.env = build_env(envp);
	if (!shell.env)
		return (1);
	shell.envp = NULL;
	shell.paths = NULL;
	shell.exit = 0;
	shell.tokens = NULL;
	run_signal(&shell);
	if (isatty(STDIN_FILENO))
		print_ascii_art();
	run_all(&shell);
	return (shell.exit);
}
