/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:48:48 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 09:57:53 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	expand_wildcards(t_list	*blocks)
{
	char	**newargs;
	t_list	*next;

	while (blocks)
	{
		next = blocks->next;
		if (!expand_wildcard(blocks->content, &newargs))
			return (0);
		if (put_args_wildcard_block(blocks, newargs))
			return (0);
		free(newargs);
		blocks = next;
	}
	return (1);
}
