/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:44:19 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/31 10:49:24 by ddelhalt         ###   ########.fr       */
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

void	exec_list(t_subtokens tokens, t_env *envp, t_list **pipeline)
{
	int			i;
	t_parsing	*cpy;

	eval_exec(subtokens_init(tokens.tokens, tokens.start, 0, tokens.sep), envp,
		pipeline);
	i = -1;
	cpy = tokens.tokens;
	while (++i < tokens.sep)
		cpy = cpy->next;
	if (is_pipeline_sigint(*pipeline))
		return ;
	while (cpy && exec_list_if(*pipeline, cpy))
	{
		if (cpy->type == LEFT_PAR)
			i += goto_par_end(&cpy);
		cpy = cpy->next;
		i++;
	}
	if (cpy)
		return (eval_exec(subtokens_init(tokens.tokens, i + 1, 0, tokens.end),
				envp, free_pipeline(pipeline)));
}
