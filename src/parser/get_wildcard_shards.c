/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wildcard_shards.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:49:30 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 14:13:15 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_shards(t_expand *block)
{
	int		count;
	int		i;
	char	*str;

	count = 0;
	i = 0;
	while (block[i].str)
	{
		if (block[i].type == DFL)
		{
			str = block[i].str;
			while (*str)
			{
				if (*str == '*')
				{
					while (*str + 1 == '*')
						str++;
					count++;
				}
				str++;
			}
		}
		i++;
	}
	return (count);
}

static char	*fill_join(char **split, int len)
{
	int		i;
	int		j;
	int		strlen;
	char	*str;

	i = 0;
	strlen = 0;
	while (i < len)
		strlen += ft_strlen(split[i++]);
	str = malloc(sizeof(char) * (strlen + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		strlen = ft_strlen(split[i]);
		ft_memcpy(str + j, split[i++], strlen);
		j += strlen;
	}
	str[j] = '\0';
	while (len)
		free(split[--len]);
	free(split);
	return (str);
}

static char	*fill_shard(int starti, int startj, t_expand content[])
{
	int		endi;
	int		endj;
	int		i;
	char	**split;

	endi = starti;
	endj = startj;
	fill_shard_get_end(&endi, &endj, content);
	if (!content[endi].str)
		endi--;
	split = malloc(sizeof(char *) * (endi - starti + 1));
	if (!split)
		return (NULL);
	if (endi - starti)
		split[0] = ft_strdup(content[starti].str + startj);
	else
		split[0] = ft_substr(content[starti].str, startj, endj - startj);
	i = 0;
	while (starti + ++i < endi)
		split[i] = ft_strdup(content[starti + i].str);
	if (starti + i <= endi)
		split[i] = ft_substr(content[starti + i].str, 0, endj);
	return (fill_join(split, endi - starti + 1));
}

static int	fill_shards(t_expand content[], char *shards[])
{
	int	i;
	int	j;
	int	starti;
	int	startj;

	i = 0;
	j = 0;
	while (content[i].str)
	{
		starti = i;
		startj = j;
		fill_shard_get_end(&i, &j, content);
		if (content[i].str)
		{
			while (content[i].str[j] == '*')
				j++;
		}
		*shards = fill_shard(starti, startj, content);
		shards++;
	}
	return (1);
}

int	get_wildcard_shards(t_expand content[], char ***shards)
{
	int	count;
	int	i;

	count = count_shards(content);
	if (!count)
		return (1);
	*shards = ft_calloc(count + 2, sizeof(char *));
	if (!shards)
		return (0);
	i = 0;
	fill_shards(content, *shards);
	return (1);
}
