/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_init_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:43:13 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/24 17:26:57 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_process	*create_process(t_subtokens tokens, int infile)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	if (!process)
		return (NULL);
	process->tokens = tokens;
	process->pid = 0;
	process->killed = 0;
	process->status = 0;
	process->infile = infile;
	process->outfile = STDOUT_FILENO;
	return (process);
}

int	pipeline_init_process(t_subtokens tokens, t_list **pipeline, int infile, int outfile)
{
	t_process	*process;
	t_list		*lst;
	int			pipe_fd[2];

	process = create_process(tokens, infile);
	if (!process)
		return (-1);
	pipe_fd[0] = STDIN_FILENO;
	if (outfile)
	{
		if (pipe(pipe_fd) == -1)
		{
			free(process);
			return (-1);
		}
		process->outfile = pipe_fd[1];
	}
	lst = ft_lstnew(process);
	if (!lst)
	{
		free(process);
		return (-1);
	}
	ft_lstadd_back(pipeline, lst);
	return (pipe_fd[0]);
}
