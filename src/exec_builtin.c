/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:07:02 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/27 01:56:51 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_builtin(char *argv[])
{
	if (!strcmp(*argv, "echo"))
		return (1);
	else if (!strcmp(*argv, "cd"))
		return (1);
	else if (!strcmp(*argv, "pwd"))
		return (1);
	else if (!strcmp(*argv, "export"))
		return (1);
	else if (!strcmp(*argv, "unset"))
		return (1);
	else if (!strcmp(*argv, "env"))
		return (1);
	else if (!strcmp(*argv, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(char *argv[], char **envp[], t_process *process,
		t_list **pipeline)
{
	if (!strcmp(*argv, "echo"))
		return (builtin_echo(argv, process->outfile));
	else if (!strcmp(*argv, "cd"))
		return (builtin_cd(argv));
	else if (!strcmp(*argv, "pwd"))
		return (builtin_pwd());
	else if (!strcmp(*argv, "export"))
		return (builtin_export(argv, envp));
	else if (!strcmp(*argv, "unset"))
		return (builtin_unset(argv, *envp));
	else if (!strcmp(*argv, "env"))
		return (builtin_env(*envp, process->outfile));
	return (builtin_exit(argv, *envp, process->tokens.tokens, pipeline));
}
