/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:04 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/24 16:12:25 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	killed_printer(t_list *pipeline)
{
	t_process	*process;

	if (is_pipeline_sigint(pipeline))
		ft_printf_fd(2, "\n");
	else
	{
		pipeline = ft_lstlast(pipeline);
		process = pipeline->content;
		if (process->killed && get_status(process->status) == SIGQUIT)
			ft_printf_fd(2, "Quit (core dumped)\n");
		else if (process->killed && get_status(process->status) == SIGTERM)
			ft_printf_fd(2, "Terminated\n");
		else if (process->killed)
			ft_printf_fd(2, "\n");
	}
}

static void	wait_pipeline(t_list **pipeline)
{
	t_list		*cpy;
	t_process	*process;

	cpy = *pipeline;
	while (cpy)
	{
		process = cpy->content;
		if (process->pid)
		{
			waitpid(process->pid, &process->status, 0);
			if (WIFSIGNALED(process->status))
				process->killed = 1;
		}
		cpy = cpy->next;
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
		if (process->infile != STDIN_FILENO)
			close(process->infile);
		if (process->outfile != STDOUT_FILENO)
			close(process->outfile);
		cpy = cpy->next;
	}
	wait_pipeline(pipeline);
	envp->code = get_shell_code(*pipeline);
	killed_printer(*pipeline);
}
