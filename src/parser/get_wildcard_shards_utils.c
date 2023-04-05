/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard_shards_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:13:23 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 14:13:48 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	fill_shard_get_end(int *i, int *j, t_expand content[])
{
	int	starti;

	starti = *i;
	while (content[*i].str)
	{
		if (content[*i].type == DFL)
		{
			if (*i != starti)
				*j = 0;
			while (content[*i].str[*j])
			{
				if (content[*i].str[*j] == '*')
					return ;
				(*j)++;
			}
		}
		(*i)++;
	}
}
