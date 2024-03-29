/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:00:33 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 20:11:14 by ddelhalt         ###   ########.fr       */
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

static int	splitlen(char *str)
{
	char	*next;
	int		len;

	len = 0;
	while (*str && !ft_isspace(*str))
	{
		next = NULL;
		if (*str == '"')
			next = ft_strchr(str + 1, '"');
		else if (*str == '\'')
			next = ft_strchr(str + 1, '\'');
		if (next)
		{
			len += next - str;
			str = next;
		}
		len++;
		str++;
	}
	return (len);
}

static int	fill_split(char **str, int i, char ***split)
{
	int		strlen;

	strlen = splitlen(*str);
	(*split)[i] = ft_substr((*str), 0, strlen);
	if (!(*split)[i])
	{
		clear_split(split);
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
