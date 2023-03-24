/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:35:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/24 12:36:45 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	open_fd(int *fd, int default_fd, char *path, int flags)
{
	if (*fd != default_fd)
		close(*fd);
	return (open(path, flags));
}

static	int	open_fd_in(int *fd, char *path)
{
	*fd = open_fd(fd, STDIN_FILENO, path, O_RDONLY);
	return (1);
}

static	int	open_fd_out(int *fd, char *path, int flag)
{
	int	flags;

	flags = O_WRONLY | O_CREAT
		| S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	*fd = open_fd(fd, STDOUT_FILENO, path, flags | flag);
	return (1);
}

static	char	put_new_fd_redirec(t_parsing *tokens, int *fd_out, int *fd_in)
{
	if (tokens->type == R_INPUT)
		return (open_fd_in(fd_in, tokens->next->content));
	else if (tokens->type == R_OUTPUT)
		return (open_fd_out(fd_out, tokens->next->content, O_TRUNC));
	else if (tokens->type == R_DOUTPUT)
		return (open_fd_out(fd_out, tokens->next->content, O_APPEND));
	else if (tokens->type == R_DINPUT)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = tokens->fd;
		return (1);
	}
	return (0);
}

char	set_fd_redirect(int *fd_in, int *fd_out, t_parsing *tokens, int redirs)
{
	while (redirs--)
	{
		while (!put_new_fd_redirec(tokens, fd_out, fd_in))
			tokens = tokens->next;
		tokens = tokens->next;
		if (*fd_out == -1 || *fd_in == -1)
			return (perror(tokens->content), 1);
		tokens = tokens->next;
	}
	return (0);
}
