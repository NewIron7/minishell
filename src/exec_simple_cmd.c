/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:49:34 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/03 19:17:22 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	set_on_cmd(t_parsing **tokens, int start)
{
	int	i;

	i = -1;
	while (++i < start)
		*tokens = *tokens->next;
	return (tokens);
}

static char	check_redirection(t_parsing *tokens, int end)
{
	int	i;

	i = -1;
	while (++i < end)
	{
		if (tokens->type == R_INPUT || tokens->type == R_OUTPUT
			|| tokens->type == R_DINPUT || tokens->type == R_DOUTPUT)
			return (tokens->type);
		tokens = tokens->next;
	}
	return (-1);
}

static void	set_fd_redirection(int *fd_in, int *fd_out, t_parsing *tokens, int end)
{
	int	fd;
	int	i;

	i = -1;
	*fd_in = STDIN_FILENO;
	*fd_out = STDOUT_FILENO;
	while (++i < end)
	{
		if (tokens->type == R_INPUT)
			*fd_in = open(tokens->next->content, O_RDONLY);
		else if (tokens->type == R_OUTPUT)
			*fd_out = open(tokens->next->content, O_WRONLY);
		else if (tokens->type == R_DOUTPUT)
			*fd_out = open(tokens->next->content, O_APPEND);
		if (*fd_in != STIN_FILENO || *fd_out != STDOUT_FILENO)
			break ;
		tokens = tokens->next;
	}
}

static void	get_args(t_parsing *tokens, int end, char *args[])
{
	int	i;

	i = -1;
	while (++i < end)
	{
		args[i] = tokens->content;
		tokens = tokens->next;
	}
}

int	exec_simple_cmd(t_parsing *tokens, int start, int end, char *envp)
{
	char	redir;
	int		fd_in;
	int		fd_out;
	char	*args[ARG_MAX];

	set_on_cmd(tokens);
	redir = check_redirection(tokens, end - start);
	if (redir != -1)
			set_fd_redirection(&fd_in, &fd_out, tokens, end - start);
	get_args(tokens, end, args);
	return (exec_cmd(args, &envp, fd_in, fd_out));
}
