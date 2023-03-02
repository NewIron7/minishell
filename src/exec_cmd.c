/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:31:20 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/02 20:29:38 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *argv[], char *envp[], int fd_in, int fd_out)
{
	char	*path;

	if (fd_in != STDIN_FILENO)
		redirect_in(fd_in);
	if (fd_out != STDOUT_FILENO)
		redirect_out(fd_out);
	path = search_path(*argv, envp);
	if (!path)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", *argv);
		return (127);
	}
	execve(*argv, argv, envp);
	perror("minishell");
	exit(126);
}

static void	set_on_cmd(t_parsing *tokens, int start)
{
	int	i;

	i = -1;
	while (++i < start)
		tokens = tokens->next;
	return (tokens);
}

static char	check_redirection(t_parsing *tokens)
{
	while (tokens)
	{
		if (tokens->type == R_INPUT || tokens->type == R_OUTPUT
			|| tokens->type == R_DINPUT || tokens->type == R_DOUTPUT)
			return (tokens->type);
		tokens = tokens->next;
	}
	return (-1);
}

char	exec_simple_cmd(t_parsing *tokens, int start, int end, char *envp)
{
	char	redir;

	tokens = set_on_cmd(tokens);
	redir = check_redirection(tokens);
	if (redir != -1)
		
}
