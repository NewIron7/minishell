/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:04 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/31 10:05:19 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	killed_printer(t_list *pipeline)
{
	t_process	*process;

	if (is_pipeline_sigint(pipeline))
		ft_printf("\n");
	else
	{
		pipeline = ft_lstlast(pipeline);
		process = pipeline->content;
		if (process->killed)
			ft_printf("\n");
	}
}

static void	close_pipeline(t_list *pipeline)
{
	t_process	*process;

	while (pipeline)
	{
		process = pipeline->content;
		if (process->infile != STDIN_FILENO && process->infile != -1)
		{
			close(process->infile);
			process->infile = STDIN_FILENO;
		}
		if (process->outfile != STDOUT_FILENO && process->outfile != -1)
		{
			close(process->outfile);
			process->outfile = STDOUT_FILENO;
		}
		pipeline = pipeline->next;
	}
}

static void	wait_pipeline(t_list *pipeline)
{
	t_process	*process;

	close_pipeline(pipeline);
	while (pipeline)
	{
		process = pipeline->content;
		if (process->pid)
		{
			waitpid(process->pid, &process->status, 0);
			if (WIFSIGNALED(process->status))
				process->killed = 1;
		}
		pipeline = pipeline->next;
	}
}

void	exec_pipeline(t_subtokens tokens, t_env *envp, t_list **pipeline)
{
	t_list		*cpy;
	t_process	*process;
	int			need_fork;

	fill_pipeline(tokens, pipeline);
	if (!*pipeline)
	{
		perror("minishell");
		return ;
	}
	cpy = *pipeline;
	need_fork = (cpy->next != 0);
	while (cpy)
	{
		process = cpy->content;
		exec_simple_cmd(process, envp, need_fork, pipeline);
		cpy = cpy->next;
	}
	wait_pipeline(*pipeline);
	envp->code = get_shell_code(*pipeline);
	killed_printer(*pipeline);
}
