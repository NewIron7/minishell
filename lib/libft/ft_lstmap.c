/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 02:49:57 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/30 16:53:27 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnewmap(t_list *l, void *(*f)(void *), void (*d)(void *))
{
	void	*content;
	t_list	*new;

	content = (*f)(l->content);
	if (!content)
		return (NULL);
	new = ft_lstnew(content);
	if (!new)
	{
		(*d)(content);
		return (NULL);
	}
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*last;

	new = ft_lstnewmap(lst, f, del);
	if (!new)
		return (NULL);
	last = new;
	lst = lst->next;
	while (lst)
	{
		last->next = ft_lstnewmap(lst, f, del);
		if (!last->next)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		last = last->next;
		lst = lst->next;
	}
	return (new);
}
