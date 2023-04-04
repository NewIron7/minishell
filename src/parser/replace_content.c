/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:50:57 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/04 16:07:21 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	init_replace_content(t_expand split[], t_parsing *elem)
{
	char	*ncontent;

	if (split && split->str)
	{
		ncontent = ft_strdup(split->str);
		if (ncontent == NULL)
			return (1);
		free(elem->content);
		elem->content = ncontent;
		return (0);
	}
	return (1);
}

static char	join_on_elem(char **content, char *str)
{
	char	*ncontent;

	ncontent = ft_strjoin(*content, str);
	if (ncontent == NULL)
		return (1);
	free(*content);
	*content = ncontent;
	return (0);
}

static char	replace_content_elem(t_expand split[], t_parsing *elem)
{
	int	i;

	if (init_replace_content(split, elem))
		return (1);
	i = 1;
	while (split[i].str)
	{
		if (join_on_elem(&elem->content, split[i].str))
			return (1);
		i++;
	}
	return (0);
}

static char	create_elem_replace_content(t_expand split[], t_parsing **elem)
{
	t_parsing	*nelem;
	char		*str;
	t_parsing	*tmp;

	str = ft_strdup("");
	if (str == NULL)
		return (1);
	nelem = ft_lstnew_parsing(str, ARG);
	if (nelem == NULL)
		return (1);
	if (replace_content_elem(split, nelem))
		return (free(nelem), 1);
	tmp = (*elem)->next;
	(*elem)->next = nelem;
	nelem->prev = (*elem);
	nelem->next = tmp;
	*elem = tmp;
	return (0);
}

char	replace_content(t_list *block, t_parsing *elem)
{
	t_expand	*split;

	split = block->content;
	if (replace_content_elem(split, elem))
		return (1);
	block = block->next;
	while (block)
	{
		split = block->content;
		if (create_elem_replace_content(split, &elem))
			return (1);
		block = block->next;
	}
	return (0);
}
