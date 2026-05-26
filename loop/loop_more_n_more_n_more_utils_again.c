/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_more_n_more_n_more_utils_again.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:48:40 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/26 18:43:58 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_str(char *dir, char *ret)
{
	if (!getcwd(dir, PATH_MAX))
	{
		if (!ret || !ret[0])
			return (NULL);
		return (ft_strjoin(ret, "$ "));
	}
	ft_strlcpy(ret, dir, ft_strlen(dir) + 1);
	return (ft_strjoin(dir, "$ "));
}
