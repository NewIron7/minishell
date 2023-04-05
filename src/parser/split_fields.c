/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:45:46 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 14:20:46 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_list	*fill_new_elem(char *str, t_expand *split, int len)
{
	t_list		*new_elem;
	t_expand	*content;
	int			i;

	content = malloc(sizeof(t_expand) * (len + 1));
	if (!content)
		return (NULL);
	i = 0;
	if (str)
	{
		content[0].str = str;
		content[0].type = DFL;
		i = 1;
	}
	while (i < len)
	{
		content[i] = split[i];
		i++;
	}
	content[i].str = NULL;
	new_elem = ft_lstnew(content);
	if (!new_elem)
		free(content);
	return (new_elem);
}

static int	new_block(char *new_str, t_list *blocks, int index)
{
	t_expand	*split;
	t_list		*new_elem;
	int			len;

	split = blocks->content;
	len = 0;
	while (split[index + len + 1].str)
		len++;
	if (new_str)
		len++;
	new_elem = fill_new_elem(new_str, split + index, len);
	if (!new_elem)
		return (0);
	ft_lstadd_back(&blocks, new_elem);
	split[index + 1].str = NULL;
	return (1);
}

static int	fonction_hugo(t_list *blocks, int index, int strindex, char *str)
{
	char		*new_str;
	int			err;

	str[strindex] = '\0';
	while (str[++strindex])
	{
		if (!ft_strchr(" \n\t", str[strindex]))
			break ;
	}
	if (!str[strindex])
		err = new_block(NULL, blocks, index);
	else
	{
		new_str = ft_substr(str + strindex, 0, ft_strlen(str + strindex));
		if (!new_str)
			return (0);
		err = new_block(new_str, blocks, index);
	}
	return (err);
}

static int	expand_blocks(t_list *blocks)
{
	t_expand	*split;
	int			i;
	int			j;

	while (blocks->next)
		blocks = blocks->next;
	split = blocks->content;
	i = 0;
	while (split[i].str)
	{
		if (split[i].type == DFL)
		{
			j = 0;
			while (split[i].str[j])
			{
				if (ft_strchr(" \n\t", split[i].str[j]))
					return (fonction_hugo(blocks, i, j, split[i].str));
				j++;
			}
		}
		i++;
	}
	if (!split[i].str)
		return (0);
	return (1);
}

int	split_fields(t_expand split[], t_list **blocks)
{
	int	added;

	trim_fields(split);
	*blocks = init_blocks(split);
	if (!*blocks)
		return (0);
	added = expand_blocks(*blocks);
	while (added > 0)
		added = expand_blocks(*blocks);
	if (added < 0)
		return (0);
	return (1);
}
