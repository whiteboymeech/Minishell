/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:03:01 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/08 23:24:20 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

long	ft_atol(const char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

static int	is_out_of_range(const char *str)
{
	unsigned long long	res;
	int					i;
	int					sign;

	res = 0;
	i = 0;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (sign == 1 && res > (unsigned long long)LONG_MAX)
			return (1);
		if (sign == -1 && res > (unsigned long long)LONG_MIN)
			return (1);
	}
	return (0);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	verify_args(t_tok *arg, t_minish *shell)
{
	if (!arg || arg->type == TOKEN_EOF)
	{
		make_dissapear(shell);
		exit(shell->exit);
	}
	if (!is_numeric(arg->value) || is_out_of_range(arg->value))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg->value, 2);
		ft_putendl_fd(": numeric argument required", 2);
		make_dissapear(shell);
		exit(2);
	}
}

int	ft_exit(t_tok *tokens, t_minish *shell)
{
	t_tok	*arg;
	int		code;

	code = 0;
	arg = tokens->next;
	verify_args(arg, shell);
	if (arg->next && arg->next->type == TOKEN_WORD)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	code = ft_atol(arg->value);
	make_dissapear(shell);
	exit((unsigned char)code);
}
