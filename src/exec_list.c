/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 07:44:19 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/08 14:14:06 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_list(t_subtokens tokens, char *envp[])
{
	int			ret;
	int			i;
	t_parsing	*cpy;

	ret = eval_exec(subtokens_init(tokens.tokens, tokens.start, 0, tokens.sep), envp);
	i = -1;
	cpy = tokens.tokens;
	while (++i < tokens.sep)
		cpy = cpy->next;
	if ((ret && cpy->type == AND) || (!ret && cpy->type == OR))
		return (eval_exec(subtokens_init(tokens.tokens, tokens.sep + 1, 0, tokens.end), envp));
	cpy = cpy->next;
	i++;
	while ((cpy && (ret && cpy->type != AND)) || ((!ret && cpy->type != OR)))
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
		return (eval_exec(subtokens_init(tokens.tokens, i + 1, 0, tokens.end), envp));
	else
		return (ret);
}
