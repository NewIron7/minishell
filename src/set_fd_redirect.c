/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 12:35:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/03 03:36:29 by ddelhalt         ###   ########.fr       */
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

static void	put_new_fd_redirec(t_parsing *elem, int *fd_in, int *fd_out)
{
	if (elem->type == R_INPUT)
		open_fd_in(fd_in, elem->next->content);
	else if (elem->type == R_OUTPUT)
		open_fd_out(fd_out, elem->next->content, O_TRUNC);
	else if (elem->type == R_DOUTPUT)
		open_fd_out(fd_out, elem->next->content, O_APPEND);
	else if (elem->type == R_DINPUT)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = elem->fd;
	}
}

char	set_fd_redirect(int *fd_in, int *fd_out, t_parsing *elem, int redirs)
{
	while (redirs--)
	{
		while (!is_redirect(elem))
			elem = elem->next;
		put_new_fd_redirec(elem, fd_in, fd_out);
		elem = elem->next;
		if (*fd_out == -1 || *fd_in == -1)
		{
			ft_printf_fd(2, "minishell: ");
			return (perror(elem->content), 1);
		}
		elem = elem->next;
	}
	return (0);
}
