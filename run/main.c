/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenois <mabenois@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 18:25:47 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/26 18:23:41 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minish	shell;

	(void)av;
	(void)ac;
	shell.env = build_env(envp);
	shell.envp = NULL;
	shell.paths = NULL;
	shell.exit = 0;
	shell.tokens = NULL;
	run_signal();
	run_all(&shell);
	free_env(shell.env);
	rl_clear_history();
	return (shell.exit);
}
