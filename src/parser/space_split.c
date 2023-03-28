/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:00:33 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 18:32:42 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	while (*cpy && !ft_isspace(*cpy))
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

int	space_split(char *str, char ***split)
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
