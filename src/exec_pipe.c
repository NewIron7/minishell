/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:04 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/09 23:34:48 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_pipe_out(t_subtokens tokens, char **envp[], int fd)
{
	int	pid;
	int	status;

	pid	= fork();
	if (pid == -1)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	if (pid)
	{
		close(fd);
		waitpid(pid, &status, 0);
		return (status);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			exit(EXIT_FAILURE);
		}
		close(fd);
		exit(eval_exec(tokens, envp));
	}
}

int	exec_pipe(t_subtokens tokens, char **envp[])
{
	int			pid;
	int			pipe_fd[2];
	int			status;

	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (EXIT_FAILURE);
	}
	if (pid)
	{
		close(pipe_fd[1]);
		status = exec_pipe_out(subtokens_init(tokens.tokens, tokens.sep + 1, 0, tokens.end), envp, pipe_fd[0]);
		waitpid(pid, NULL, 0);
		return (status);
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[1]);
		exit(eval_exec(subtokens_init(tokens.tokens, tokens.start, 0, tokens.sep), envp));
	}
}
