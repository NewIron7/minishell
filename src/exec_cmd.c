/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:31:20 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/06 18:30:07 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *argv[], char *envp[], int fd_in, int fd_out)
{
	char	*path;
	pid_t	pid;
	int		status;
	int		waitoptions;

	if (fd_in != STDIN_FILENO)
		redirect_in(fd_in);
	if (fd_out != STDOUT_FILENO)
		redirect_out(fd_out);
	path = search_path(*argv, envp);
	if (!path && !get_exec_path(*argv))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", *argv);
		return (127);
	}
	else if (get_exec_path(*argv))
		path = *argv;
	status = 0;
	waitoptions = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, envp) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
		//exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, waitoptions);
		return (status);
	}
	else
	{
		perror("minishell");
		return (127);
	}
}
