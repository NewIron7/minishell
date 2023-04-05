/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:47:45 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 08:45:25 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eval_exec(t_parsing **parsing, t_portion chunck,
	t_env *envp, t_list **pipeline)
{
	t_parsing	*cpy;

	*pipeline = NULL;
	cpy = chunck.start;
	if (!cpy)
		cpy = *parsing;
	while (cpy != chunck.end)
	{
		if (cpy->type == AND || cpy->type == OR)
			return (exec_list(parsing, set_portion(chunck.start, chunck.end),
					envp, pipeline));
		else if (cpy->type == LEFT_PAR)
			cpy = goto_par_end(cpy);
		cpy = cpy->next;
	}
	return (exec_pipeline(parsing, set_portion(chunck.start, chunck.end),
			envp, pipeline));
}
