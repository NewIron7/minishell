/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_txt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 18:52:23 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/20 18:49:42 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	is_type_txt(t_parsing *list_parsing)
{
	if (list_parsing)
	{
		if (list_parsing->type == TXT || list_parsing->type == TXT_S
			|| list_parsing->type == TXT_D || list_parsing->type == ARG)
			return (1);
	}
	return (0);
}

static char	join_elem_parsing(t_parsing *elem)
{
	char		*n_content;
	t_parsing	*next;

	next = elem->next;
	n_content = ft_strjoin(elem->content, next->content);
	if (n_content == NULL)
		return (1);
	if (next->next)
		next->next->prev = elem;
	elem->next = next->next;
	free(elem->content);
	free(next->content);
	free(next);
	elem->content = n_content;
	elem->type = ARG;
	return (0);
}

static void	delete_elem_parsing(t_parsing *elem)
{
	t_parsing	*prev;
	t_parsing	*next;

	prev = elem->prev;
	next = elem->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(elem->content);
	free(elem);
}

char	gather_txt(t_parsing *list_parsing)
{
	t_parsing	*tmp;

	while (list_parsing)
	{
		if (is_type_txt(list_parsing) && is_type_txt(list_parsing->next))
		{
			if (join_elem_parsing(list_parsing))
				return (1);
		}
		else if (is_type_txt(list_parsing))
		{
			list_parsing->type = ARG;
			list_parsing = list_parsing->next;
		}
		else
		{
			tmp = list_parsing;
			list_parsing = list_parsing->next;
			if (tmp->type == SPACE_TMP)
				delete_elem_parsing(tmp);
		}
	}
	return (0);
}
