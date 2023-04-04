/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:44:19 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/04 15:31:35 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipeline_sigint(t_list *pipeline)
{
	t_process	*process;

	while (pipeline)
	{
		process = pipeline->content;
		if (process->killed && get_status(process->status) == SIGINT)
			return (1);
		pipeline = pipeline->next;
	}
	return (0);
}

int	pipeline_status(t_list *pipeline)
{
	t_process	*process;

	pipeline = ft_lstlast(pipeline);
	process = pipeline->content;
	return (get_status(process->status));
}

static char	exec_list_if(t_list *pipeline, t_parsing *cpy)
{
	if ((!pipeline_status(pipeline) && cpy->type != AND)
		|| (pipeline_status(pipeline) && cpy->type != OR))
		return (1);
	return (0);
}

void	exec_list(t_parsing **parsing, t_portion chunck, t_env *envp, t_list **pipeline)
{
	t_parsing	*cpy;

	cpy = chunck.start;
	if (!cpy)
		cpy = *parsing;
	while (cpy->type != AND && cpy->type != OR)
		cpy = cpy->next;
	eval_exec(parsing, set_portion(chunck.start, cpy), envp, pipeline);
	if (is_pipeline_sigint(*pipeline))
		return ;
	while (cpy != chunck.end && exec_list_if(*pipeline, cpy))
	{
		if (cpy->type == LEFT_PAR)
			cpy = goto_par_end(cpy);
		cpy = cpy->next;
	}
	if (cpy)
		return (eval_exec(parsing, set_portion(cpy->next, chunck.end), envp, free_pipeline(pipeline)));
}
