/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 01:08:44 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 02:14:45 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

// char	*build_prompt(char *dir)
// {
	// char	*ret;
	// char	*prompt;
// 
	// ret = ft_strjoin(dir, "$ ");
	// if (!ret)
	// {
		// free(dir);
		// return (NULL);
	// }
	// prompt = ft_strjoin("Jean Moulin & De Gaulle 2000:", ret);
	// if (!prompt)
	// {
		// free(ret);
		// return (NULL);
	// }
	// free(ret);
	// free(dir);
	// return (prompt);
// }
// 
// int	ft_read_prompt(char **ret)
// {
	// char	*dir;
	// char	*prompt;
// 
	// dir = getcwd(NULL, 0);
	// prompt = build_prompt(dir);
	// *ret = readline(prompt);
	// free(prompt);
	// if (!(*ret))
	// {
		// dup2(5, 0);
		// if (g_sig != SIGINT)
		// {
			// *ret = ft_strdup("exit");
			// if (!ret)
				// return (-1);
			// g_sig = -1;
		// }
		// else
		// {
			// g_sig = -1;
			// return (1);
		// }
	// }
	// return (0);
// }
