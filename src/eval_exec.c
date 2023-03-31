/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:47:45 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/31 10:48:58 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parsing	*init_eval_exec(int *i, t_subtokens tokens,
	t_list **pipeline)
{
	*i = -1;
	*pipeline = NULL;
	return (tokens.tokens);
}

void	eval_exec(t_subtokens tokens, t_env *envp, t_list **pipeline)
{
	int			i;
	t_parsing	*cpy;

	cpy = init_eval_exec(&i, tokens, pipeline);
	while (++i < tokens.start)
		cpy = cpy->next;
	while (cpy && (i < tokens.end || tokens.end == -1))
	{
		if (cpy->type == AND || cpy->type == OR)
			return (exec_list(subtokens_init(tokens.tokens, tokens.start,
						i, tokens.end), envp, pipeline));
		else if (cpy->type == LEFT_PAR)
			i += goto_par_end(&cpy);
		cpy = cpy->next;
		i++;
	}
	return (exec_pipeline(subtokens_init(tokens.tokens, tokens.start,
				0, tokens.end), envp, pipeline));
}
