/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:38:46 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 18:27:13 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	expand_elem(t_parsing *elem, int (*splitter)(char *, char ***))
{
	char		**split;
	t_parsing	*next;
	t_parsing	*new;
	int			i;

	split = NULL;
	if (!splitter(elem->content, &split))
		return (0);
	if (!split)
		return (1);
	i = 0;
	next = elem->next;
	while (split[i])
	{
		if (i)
		{
			new = ft_lstnew_parsing(split[i], ARG);
			if (!new)
			{
				while (split[i])
					free(split[i]);
				free(split);
				return (0);
			}
			new->prev = elem;
			elem->next = new;
		}
		else
		{
			new = elem;
			free(new->content);
		}
		new->content = split[i];
		elem = new;
		i++;
	}
	new->next = next;
	if (next)
		next->prev = new;
	free(split);
	return (1);
}
