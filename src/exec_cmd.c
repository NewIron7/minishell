/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:31:20 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/14 04:27:38 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *argv[], char *envp[], t_process *process, t_list **pipeline)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (process->infile != STDIN_FILENO)
		redirect_in(process->infile);
	if (process->outfile != STDOUT_FILENO)
		redirect_out(process->outfile);
	if (ft_strchr(*argv, '/'))
		path = *argv;
	else
		path = search_path(*argv, envp);
	if (!path)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", *argv);
		free_all(process->tokens.tokens, envp, pipeline, argv);
		exit(127);
	}
	execve(path, argv, envp);
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	perror(path);
	free_all(process->tokens.tokens, envp, pipeline, argv);
	exit(126);
}
