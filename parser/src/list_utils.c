/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:32:00 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/03 19:18:32 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

t_parsing	*ft_lstnew_parsing(char *content, char type)
{
	t_parsing	*new;

	new = malloc(sizeof(t_parsing));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_parsing	*ft_lstlast_parsing(t_parsing *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	else
		return (NULL);
}

void	ft_lstadd_back_parsing(t_parsing **lst, t_parsing *new)
{
	t_parsing	*ptr;

	if (lst)
	{
		if (*lst)
		{
			ptr = ft_lstlast_parsing(*lst);
			ptr->next = new;
			new->prev = ptr;
		}
		else
			*lst = new;
	}
}
