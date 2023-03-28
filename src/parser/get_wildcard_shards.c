/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard_shards.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:49:30 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 20:10:48 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_shards(char *str)
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
		else if (*str == '*')
		{
			while (*str + 1 == '*')
				str++;
			count++;
		}
		if (next)
			str = next;
		str++;
	}
	return (count);
}

static int	wildlen(char *str)
{
	int		len;
	char	*next;

	len = 0;
	while (*str && *str != '*')
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

static int	fill_shards(char **str, int i, char ***shards)
{
	int		strlen;

	strlen = wildlen(*str);
	(*shards)[i] = ft_substr((*str), 0, strlen);
	if (!(*shards)[i])
	{
		clear_split(shards);
		return (0);
	}
	(*str) += strlen;
	return (1);
}

int	get_wildcard_shards(char *str, char ***shards)
{
	int	count;
	int	i;

	count = count_shards(str);
	if (!count)
		return (1);
	*shards = ft_calloc(count + 2, sizeof(char *));
	if (!shards)
		return (0);
	i = 0;
	while (i <= count)
	{
		if (!fill_shards(&str, i++, shards))
			return (0);
		while (*str == '*')
			str++;
	}
	return (1);
}
