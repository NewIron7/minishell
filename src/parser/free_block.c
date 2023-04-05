/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:38:32 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/05 08:31:01 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_split(t_expand *split)
{
	int	i;

	i = 0;
	while (split[i].str)
	{
		free(split[i].str);
		i++;
	}
	free(split);
}

void	free_block(t_list *block)
{
	t_list		*next;

	while (block)
	{
		free_split(block->content);
		next = block->next;
		free(block);
		block = next;
	}
}
