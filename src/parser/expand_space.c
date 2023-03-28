/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:00:33 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 16:19:46 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	space_split(char *str, char ***split)
{
	int	count;
	int	i;

	while (*str && ft_isspace(*str))
		str++;
	count = count_split(str);
	if (!count)
		return (1);
	*split = ft_calloc(count + 2, sizeof(char *));
	if (!*split)
		return (0);
	i = 0;
	while (i <= count)
	{
		if (!fill_split(&str, i++, split))
			return (0);
		while (ft_isspace(*str))
			str++;
	}
	return (1);
}

static char	init_expand_space(t_parsing *elem, char ***split,
		t_parsing **next, int *i)
{
	*i = -1;
	*next = elem->next;
	split = NULL;
	if (!space_split(elem->content, split))
		return (0);
	if (!split)
		return (1);
	return (0);
}

static void	free_split_expand_space(char **split, int i)
{
	while (split[i])
		free(split[i]);
	free(split);
}

static void	end_expand_space(t_parsing *new, t_parsing *next)
{
	new->next = next;
	if (next)
		next->prev = new;
}

int	expand_space(t_parsing *elem)
{
	char		**split;
	t_parsing	*next;
	t_parsing	*new;
	int			i;

	if (init_expand_space(elem, &split, &next, &i))
		return (1);
	while (split[++i])
	{
		if (i)
		{
			new = ft_lstnew_parsing(split[i], ARG);
			if (!new)
				return (free_split_expand_space(split, i), 0);
			new->prev = elem;
			elem->next = new;
		}
		else
			new = elem;
		new->content = split[i];
		elem = new;
	}
	return (end_expand_space(new, next), free(split), 1);
}	
