/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_args_wildcard_block.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:12:21 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/04 19:50:31 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char		free_block_content(t_list *block)
{
	t_expand	*split;
	int			i;

	split = (t_expand *)block->content;
	i = 0;
	while (split[i].str)
	{
		free(split[i].str);
		i++;
	}
	free(split);
	return (0);
}

static	t_expand	*create_split(char *str)
{
	t_expand	*split;

	split = malloc(sizeof(t_expand) * 2);
	if (split == NULL)
		return (NULL);
	split[1].str = NULL;
	split[0].str = str;
	split[0].type = DFL;
	return (split);
}

static char	modif_block(t_list *block, char *str)
{
	t_expand	*split;

	split = create_split(str);
	if (split == NULL)
		return (1);
	free_block_content(block);
	block->content = split;
	return (0);
}

static	char	add_new_block(t_list **block, char *str)
{
	t_list		*nblock;
	t_list		*tmp;
	t_expand	*split;

	split = create_split(str);
	if (split == NULL)
		return (1);
	nblock = ft_lstnew(split);
	if (nblock == NULL)
		return (free(split), 1);
	tmp = (*block)->next;
	(*block)->next = nblock;
	nblock->next = tmp;
	*block = nblock;
	return (0);
}

char	put_args_wildcard_block(t_list *block, char *newargs[])
{
	int		i;

	if (newargs == NULL || *newargs == NULL)
		return (1);
	if (modif_block(block, newargs[0]))
		return (1);
	i = 1;
	while (newargs[i])
	{
		if (add_new_block(&block, newargs[i]))
			return (1);
		i++;
	}
	return (0);
}
