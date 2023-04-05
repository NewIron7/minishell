/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fields_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:21:01 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 14:21:39 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	trim_fields(t_expand split[])
{
	int	len;

	if (split->type == DFL)
	{
		len = 0;
		while (ft_strchr(" \t\n", split->str[len]))
			len++;
		if (len)
			ft_memmove(split->str, split->str + len,
				ft_strlen(split->str + len) + 1);
	}
	while ((split + 1)->str)
		split++;
	if (split->type == DFL)
	{
		len = ft_strlen(split->str);
		while (len > 0 && ft_strchr(" \t\n", split->str[len - 1]))
			len--;
		split->str[len] = '\0';
	}
}

t_list	*init_blocks(t_expand split[])
{
	t_list	*blocks;

	blocks = ft_lstnew(split);
	if (!blocks)
		return (NULL);
	return (blocks);
}
