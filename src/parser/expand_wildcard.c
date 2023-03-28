/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:48:48 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 18:25:03 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_split(char ***split)
{
	size_t	i;

	i = 0;
	while ((*split)[i])
		free((*split)[i++]);
	free(*split);
	*split = NULL;
}

static char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;

	if (!*little)
		return ((char *) big);
	while (*big)
	{
		i = 0;
		while (little[i] && big[i] == little[i])
			i++;
		if (!little[i])
			return ((char *) big);
		big++;
	}
	return (NULL);
}

static int	is_matching_end(char *file, char *to_match)
{
	int	i;
	int	j;

	i = ft_strlen(to_match);
	j = ft_strlen(file);
	if (j < i)
		return (0);
	while (i > 0)
	{
		if (file[--j] != to_match[--i])
			return (0);
	}
	return (1);
}

static int	is_matching(char **shards, char *file)
{
	int	i;

	i = 0;
	if (**shards)
	{
		if (ft_strncmp(*shards, file, ft_strlen(*shards)))
			return (0);
		i++;
		file += ft_strlen(*shards);
	}
	while (shards[i + 1])
	{
		file = ft_strstr(file, shards[i]);
		if (!file)
			return (0);
		i++;
	}
	if (!is_matching_end(file, shards[i]))
		return (0);
	return (1);
}

static int	add_match(char *file, char **matches[], size_t *size)
{
	char	**new_matches;
	size_t	i;

	(*size)++;
	new_matches = malloc(sizeof(char *) * (*size + 1));
	if (!new_matches)
		return (0);
	i = 0;
	while (i + 1 < *size)
	{
		new_matches[i] = (*matches)[i];
		i++;
	}
	free(*matches);
	*matches = new_matches;
	(*matches)[i] = ft_strdup(file);
	if (!(*matches)[i])
		return (0);
	(*matches)[i + 1] = 0;
	return (1);
}

static int	exp_from_shards(char **shards, char ***split)
{
	DIR				*dir;
	struct dirent	*entry;
	size_t			size;

	dir = opendir(".");
	if (!dir)
		return (0);
	size = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (is_matching(shards, entry->d_name))
		{
			if (!add_match(entry->d_name, split, &size))
			{
				free_split(split);
				closedir(dir);
				perror("minishell");
				return (0);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (1);
}

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

static int	fill_shards(char **str, int i , char ***shards)
{
	int		strlen;
	char	*next;
	char	*cpy;

	strlen = 0;
	cpy = *str;
	while (*cpy && *cpy != '*')
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
	(*shards)[i] = ft_substr((*str), 0, strlen);
	if (!(*shards)[i])
	{
		free_split(shards);
		return (0);
	}
	(*str) += strlen;
	return (1);
}

static int	get_shards(char *str, char ***shards)
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

int	expand_wildcard(char *str, char ***split)
{
	char	**shards;

	shards = NULL;
	if (!get_shards(str, &shards))
		return (0);
	if (!shards)
		return (1);
	if (!exp_from_shards(shards, split))
	{
		free_split(&shards);
		return (0);
	}
	free_split(&shards);
	return (1);
}