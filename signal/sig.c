/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 00:00:00 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/06 19:30:58 by mabenois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	g_sig = 0;

/* OLD
static void	sigint_handler(int sig)
{
	g_sig = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
*/

void	sig_handle(int sig)
{
	g_sig = sig;
	printf("\ng_sig: %d\n", g_sig);
	if (sig == SIGQUIT)
		return ;
	if (sig == SIGINT)
	{
		dup2(STDIN_FILENO, STDIN_FILENO);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	run_signal(t_minish *shell)
{
	sigemptyset(&shell->sa.sa_mask);
	sigaddset(&shell->sa.sa_mask, SIGINT);
	sigaddset(&shell->sa.sa_mask, SIGQUIT);
	shell->sa.sa_handler = sig_handle;
	sigaction(SIGINT, &shell->sa, NULL);
	sigaction(SIGQUIT, &shell->sa, NULL);
}

/* OLD
void	run_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
*/
