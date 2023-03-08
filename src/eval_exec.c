/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:47:45 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/08 15:29:43 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	eval_exec(t_subtokens tokens, char *envp[])
{
	int			i;
	t_parsing	*cpy;

	i = -1;
	cpy = tokens.tokens;
	while (++i < tokens.start)
		cpy = cpy->next;
	while (cpy && (i < tokens.end || tokens.end == -1))
	{
		if (cpy->type == AND || cpy->type == OR)
			return (exec_list(subtokens_init(tokens.tokens, tokens.start, i, tokens.end), envp));
		else if (cpy->type == PIPE)
			return (exec_pipe(subtokens_init(tokens.tokens, tokens.start, i, tokens.end), envp));
		else if (cpy->type == LEFT_PAR)
		{
			while (cpy->type != RIGHT_PAR)
			{
				cpy = cpy->next;
				i++;
			}
		}
		cpy = cpy->next;
		i++;
	}
	return (exec_simple_cmd(subtokens_init(tokens.tokens, tokens.start, 0, tokens.end), envp));
}
