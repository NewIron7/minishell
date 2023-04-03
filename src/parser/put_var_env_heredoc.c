/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_var_env_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:37:52 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/03 03:19:50 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	*get_heredoc(int fd)
{
	char	*heredoc;
	char	buf[65];
	int		rd;
	char	*tmp;

	heredoc = ft_strdup("");
	if (heredoc == NULL)
		return (NULL);
	while (1)
	{
		rd = read(fd, buf, 64);
		if (rd == 0)
			return (heredoc);
		else if (rd < 0)
			break ;
		buf[rd] = '\0';
		tmp = ft_strjoin(heredoc, buf);
		free(heredoc);
		heredoc = tmp;
		if (heredoc == NULL)
			return (NULL);
	}
	return (free(heredoc), NULL);
}

static char	put_var_env_heredoc(int *fd, char **env, int code)
{
	char	**content_env[2];
	char	*txt;
	int		tube[2];
	char	err;

	content_env[0] = env;
	txt = get_heredoc(*fd);
	content_env[1] = &txt;
	close(*fd);
	if (txt == NULL)
		return (1);
	if (pipe(tube))
		return (free(txt), 1);
	err = put_var_env_elem(content_env, code, 0, '\0');
	if (err)
		return (free(txt), err);
	write(tube[1], txt, ft_strlen(txt));
	close(tube[1]);
	free(txt);
	*fd = tube[0];
	return (0);
}

char	check_env_heredoc(t_portion chunck, t_env env)
{
	char	err;

	while (chunck.start != chunck.end)
	{
		if (chunck.start->type == LEFT_PAR)
			chunck.start = goto_par_end(chunck.start);
		else if (chunck.start->type == R_DINPUT && !chunck.start->quoted)
		{
			err = put_var_env_heredoc(&chunck.start->fd, env.env, env.code);
			if (err)
				return (err);
		}
		chunck.start = chunck.start->next;
	}
	return (0);
}
