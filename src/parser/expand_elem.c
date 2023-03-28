/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:38:46 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 19:42:35 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	create_new_elems(char **split, t_parsing *elem, t_parsing *next)
{
	int			i;
	t_parsing	*new;

	new = elem;
	i = 0;
	while (split[i])
	{
		if (i)
		{
			new = ft_lstnew_parsing(split[i], ARG);
			if (!new)
				return (i);
			new->prev = elem;
			elem->next = new;
		}
		else
			free(new->content);
		new->content = split[i];
		elem = new;
		new->next = next;
		if (next)
			next->prev = new;
		i++;
	}
	return (0);
}

int	expand_elem(t_parsing *elem, int (*splitter)(char *, char ***))
{
	char		**split;
	int			i;

	split = NULL;
	if (!splitter(elem->content, &split))
		return (0);
	if (!split)
		return (1);
	i = create_new_elems(split, elem, elem->next);
	if (i)
	{
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	free(split);
	return (1);
}
