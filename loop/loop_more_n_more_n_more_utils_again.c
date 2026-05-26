/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_more_n_more_n_more_utils_again.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 17:48:40 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/26 18:22:28 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_str(char *dir, char *ret)
{
	if (!getcwd(dir, PATH_MAX))
	{
		if (!ret)
			return (NULL);
		return (ft_strjoin(ret, "$ "));
	}
	ft_strlcpy(ret, dir, ft_strlen(dir));
	return (ft_strjoin(dir, "$ "));
}
