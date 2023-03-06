/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 17:42:48 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/06 18:52:44 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	is_redirection(t_parsing *tokens)
{
	if (tokens == NULL)
		return (0);
	if (tokens->type >= R_INPUT && tokens->type <= R_DOUTPUT)
		return (1);
	return (0);
}

char	put_new_fd_redirec(t_parsing *tokens, int *fd_out, int *fd_in)
{
	if (tokens->type == R_INPUT)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = open(tokens->next->content, O_RDONLY);
		return (1);
	}
	else if (tokens->type == R_OUTPUT)
	{
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out = open(tokens->next->content, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		return (1);
	}
	else if (tokens->type == R_DOUTPUT)
	{
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out = open(tokens->next->content, O_APPEND | O_CREAT | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		return (1);
	}
	else if (tokens->type == R_DINPUT)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = tokens->fd;
	}
	return (0);
}
