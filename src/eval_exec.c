/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 00:47:45 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/08 11:18:17 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	eval_exec(t_parsing *tokens, int start, int end, char *envp[])
{
	int			i;
	t_parsing	*cpy;

	i = -1;
	cpy = tokens;
	while (++i < start)
		cpy = cpy->next;
	while (cpy && (i < end || end == -1))
	{
		if (cpy->type == AND || cpy->type == OR)
			return (exec_list(tokens, start, end, i, envp));
		else if (cpy->type == PIPE)
			return (exec_pipe(tokens, start, end, i, envp));
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
	return (exec_simple_cmd(tokens, start, end, envp));
}
