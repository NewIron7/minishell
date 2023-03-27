/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:00:33 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/27 22:33:57 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_split(char *str)
{
	int		count;
	char	*next;

	count = 0;
	while (*str)
	{
		next = NULL;
		if (*str == '"')
			next = ft_strchr(str + 1, '"');
		else if (*str == '\'')
			next = ft_strchr(str + 1, '\'');
		else if (ft_isspace(*str))
		{
			while (ft_isspace(*str + 1))
				str++;
			if (*str + 1)
				count++;
		}
		if (next)
			str = next;
		str++;
	}
	return (count);
}

static void	free_split(char ***split)
{
	char	**cpy;

	cpy = *split;
	while (*cpy)
		free(*cpy++);
	free(*split);
	*split = NULL;
}

static int	fill_split(char **str, int i, char ***split)
{
	int		strlen;
	char	*next;
	char	*cpy;

	strlen = 0;
	cpy = *str;
	while (!ft_isspace(*cpy))
	{
		next = NULL;
		if (*cpy == '"')
			next = ft_strchr(cpy + 1, '"');
		else if (*cpy == '\'')
			next = ft_strchr(cpy + 1, '\'');
		if (next)
		{
			strlen += next - cpy;
			cpy = next;
		}
		strlen++;
		cpy++;
	}
	(*split)[i] = ft_substr((*str), 0, strlen);
	if (!(*split)[i])
	{
		free_split(split);
		return (0);
	}
	(*str) += strlen;
	return (1);
}

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

int	expand_space(t_parsing *elem)
{
	char		**split;
	t_parsing	*next;
	t_parsing	*new;
	int			i;

	split = NULL;
	if (!space_split(elem->content, &split))
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
			new = elem;
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
	
