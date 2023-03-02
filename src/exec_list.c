/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:44:19 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/02 08:34:45 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_list(t_parser tokens, int start, int end, int sep, char *envp[])
{
	int			ret;
	int			i;
	t_parsing	*cpy;

	ret = eval_exec(tokens, start, sep, envp);
	i = -1;
	cpy = tokens;
	while (++i < sep)
		cpy = cpy->next;
	if ((ret && cpy->type == AND) || (!ret && cpy->type == OR))
		return (eval_exec(tokens, sep + 1, end, envp));
	cpy = cpy->next;
	i++;
	while (cpy && (ret && cpy->type != AND) || (!ret && cpy->type != OR))
	{
		if (cpy->type == LEFT_PAR)
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
	if (cpy)
		return (eval_exec(tokens, i + 1, end, envp));
	else
		return (ret);
}
