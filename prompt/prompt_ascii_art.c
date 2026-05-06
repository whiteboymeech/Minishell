/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_ascii_art.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 01:49:07 by mabenois          #+#    #+#             */
/*   Updated: 2026/05/04 20:10:38 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../the_big_head_of_adarolla.h"

void	print_ascii_art(void)
{
	ft_putstr_fd((char *)g_banner, 1);
}
