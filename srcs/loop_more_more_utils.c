/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_more_more_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 19:35:38 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/13 20:04:15 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	handle_input(t_vars *vars, t_minish *shell)
{
	vars->lexed = lexer(vars->ret);
	if (!vars->lexed)
	{
		free(vars->ret);
		return (0);
	}
	if (validate_syntax(vars->lexed, shell))
	{
		free_lexed(vars->lexed);
		free(vars->ret);
		return (0);
	}
	return (1);
}

static int	execute_input(t_vars *vars, t_minish *shell)
{
	int	heredoc_ret;

	expand_tokens(&vars->lexed, shell);
	shell->paths = get_paths_from_env(shell->env);
	shell->tokens = vars->lexed;
	heredoc_ret = parse_pipeline(vars->lexed, shell);
	free_argv(shell->paths);
	shell->paths = NULL;
	free_lexed(vars->lexed);
	vars->lexed = NULL;
	free(vars->ret);
	vars->ret = NULL;
	return (heredoc_ret);
}

int	run_all(t_minish *shell)
{
	t_vars	vars;
	int		tmp;

	vars = (t_vars){0};
	while (1)
	{
		if (ft_read_prompt(&vars.ret) == 1)
		{
			shell->exit = 130;
			continue ;
		}
		tmp = shell->exit;
		if (!vars.ret)
			break ;
		if (*vars.ret)
			add_history(vars.ret);
		if (!handle_input(&vars, shell))
			continue ;
		if (execute_input(&vars, shell) == -1)
		{
			if (tmp == 130 && vars.ret && vars.ret[0] == 0)
				shell->exit = 130;
			break ;
		}
	}
	rl_clear_history();
	return (shell->exit);
}
