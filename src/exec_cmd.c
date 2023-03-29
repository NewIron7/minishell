/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:31:20 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/29 15:31:56 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *argv[], char *envp[], t_process *process, t_list **pipeline)
{
	char		*path;
	t_parsing	*tokens;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	tokens = process->tokens.tokens;
	if (process->infile != STDIN_FILENO)
		redirect_in(process->infile);
	if (process->outfile != STDOUT_FILENO)
		redirect_out(process->outfile);
	free_pipeline(pipeline);
	path = *argv;
	if (!ft_strchr(*argv, '/'))
		path = search_path(*argv, envp, "PATH");
	if (!path)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n", *argv);
		free_all(tokens, envp, NULL, argv);
		exit(127);
	}
	execve(path, argv, envp);
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	perror(*argv);
	free_all(tokens, envp, NULL, argv);
	exit(126);
}
