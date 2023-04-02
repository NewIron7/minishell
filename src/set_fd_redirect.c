/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:35:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/02 11:48:06 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_fd_in(int *fd, char *path)
{
	if (*fd != STDIN_FILENO)
		close(*fd);
	*fd = open(path, O_RDONLY);
}

static void	open_fd_out(int *fd, char *path, int flag)
{
	if (*fd != STDOUT_FILENO)
		close(*fd);
	*fd = open(path, O_WRONLY | O_CREAT | flag,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
}

static char	put_new_fd_redirec(t_parsing *tokens, int *fd_out, int *fd_in)
{
	if (tokens->type == R_INPUT)
		open_fd_in(fd_in, tokens->next->content);
	else if (tokens->type == R_OUTPUT)
		open_fd_out(fd_out, tokens->next->content, O_TRUNC);
	else if (tokens->type == R_DOUTPUT)
		open_fd_out(fd_out, tokens->next->content, O_APPEND);
	else if (tokens->type == R_DINPUT)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = tokens->fd;
	}
	else
		return (0);
	return (1);
}

char	set_fd_redirect(int *fd_in, int *fd_out, t_parsing *tokens, int redirs)
{
	while (redirs--)
	{
		while (!put_new_fd_redirec(tokens, fd_out, fd_in))
			tokens = tokens->next;
		tokens = tokens->next;
		if (*fd_out == -1 || *fd_in == -1)
		{
			if (*tokens->content == '\0')
				return (ft_printf_fd(2, "minishell: ambiguous redirect\n"), 1);
			return (perror(tokens->content), 1);
		}
		tokens = tokens->next;
	}
	return (0);
}
