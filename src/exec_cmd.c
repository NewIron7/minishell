/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:31:20 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/28 19:25:27 by ddelhalt         ###   ########.fr       */
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
