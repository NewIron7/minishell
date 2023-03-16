/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_var_env_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:37:52 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/16 14:32:12 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	*get_heredoc(int fd)
{
	char	*heredoc;
	char	buf[64];
	int		rd;
	char	*tmp;

	heredoc = NULL;
	while (1)
	{
		rd = read(fd, buf, 64);
		if (rd == 0)
			return (heredoc);
		else if (rd < 0)
			break ;
		tmp = ft_strjoin(heredoc, buf);
		free(heredoc);
		heredoc = tmp;
		if (heredoc == NULL)
			return (1);
	}
	if (heredoc)
		return (free(heredoc), 1);
	return (1);
}

char	put_var_env_heredoc(int *fd, char **env, int code)
{
	char	**content_env[2];
	char	*txt;
	int		tube[2];
	char	err;

	content_env[0] = env;
	txt = get_heredoc(fd);
	content_env[1] = &txt;
	close(fd);
	if (txt == NULL)
		return (1);
	if (pipe(tube))
		return(free(txt), 1);
	err = put_var_env_elem(content_env, code, 0, '\0');
	if (err)
		return (err);
	write(tube[1], txt, ft_strlen(txt));
	close(tube[1]);
	free(txt);
	return (0);
}
