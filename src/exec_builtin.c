/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:07:02 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/28 19:26:38 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(char *argv[], char **envp[], int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (!strcmp(*argv, "echo"))
		return (builtin_echo(argv, fd_out));
	else if (!strcmp(*argv, "cd"))
		return (builtin_cd(argv));
	else if (!strcmp(*argv, "pwd"))
		return (builtin_pwd());
	else if (!strcmp(*argv, "export"))
		return (builtin_export(argv, envp));
	else if (!strcmp(*argv, "unset"))
		return (builtin_unset(argv, *envp));
	else if (!strcmp(*argv, "env"))
		return (builtin_env(*envp, fd_out));
	return (builtin_exit(argv, *envp));
}
