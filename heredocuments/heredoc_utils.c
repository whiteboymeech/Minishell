/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adarolla <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 18:08:58 by adarolla          #+#    #+#             */
/*   Updated: 2026/05/09 23:34:07 by adarolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*expand_heredoc_line(char *line, t_minish *shell)
{
	char	*res;
	char	buffer[2];
	int		i;

	res = ft_strdup("");
	buffer[1] = '\0';
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			append_piece(&res, dollar(line, &i, shell));
		else
		{
			buffer[0] = line[i++];
			append_piece(&res, ft_strdup(buffer));
		}
	}
	return (res);
}

static int	write_segment(t_heredoc_ctx *ctx, char *pos, char *end)
{
	char	*seg;

	seg = ft_substr(pos, 0, end - pos);
	if (!seg)
		return (0);
	if (ft_strncmp(seg, ctx->delim, ctx->dlen) == 0 && seg[ctx->dlen] == '\0')
	{
		free(seg);
		return (0);
	}
	write(ctx->fd, seg, ft_strlen(seg));
	write(ctx->fd, "\n", 1);
	free(seg);
	return (1);
}

static void	write_last_segment(t_heredoc_ctx *ctx, char *pos)
{
	if (ft_strncmp(pos, ctx->delim, ctx->dlen) != 0 || pos[ctx->dlen] != '\0')
	{
		write(ctx->fd, pos, ft_strlen(pos));
		write(ctx->fd, "\n", 1);
	}
}

static void	write_loop(t_heredoc_ctx *ctx, char *pos)
{
	char	*end;

	while (pos && *pos)
	{
		end = ft_strnstr(pos, "\\n", ft_strlen(pos));
		if (!end)
		{
			write_last_segment(ctx, pos);
			break ;
		}
		if (!write_segment(ctx, pos, end))
			break ;
		pos = end + 2;
	}
}

void	write_from_token(t_tok *curr, t_tok *content_tok)
{
	char			*end;
	t_heredoc_ctx	ctx;

	ctx.delim = curr->next->value;
	ctx.dlen = ft_strlen(ctx.delim);
	ctx.fd = curr->pipe.p[1];
	end = ft_strnstr(content_tok->value, "\\n", ft_strlen(content_tok->value));
	if (!end)
	{
		close(ctx.fd);
		return ;
	}
	write_loop(&ctx, end + 2);
	close(ctx.fd);
}
