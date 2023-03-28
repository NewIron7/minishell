/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:48:48 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 17:02:30 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
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

static int	is_matching(char *str, char **shards, char *file)
{
	int	i;

	i = 0;
	if (*str != '*')
	{
		if (ft_strncmp(*shards, file, ft_strlen(*shards)))
			return (0);
		i++;
		file += ft_strlen(*shards);
	}
	while (shards[i])
	{
		file = ft_strstr(shards[i], file);
		if (!file)
			return (0);
		i++;
	}
	if (str[ft_strlen(str) - 1] != '*')
	{
		if (ft_strcmp(shards[i - 1], file))
			return (0);
	}
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

char	**exp_cmd_wild(char *str)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	size_t			size;
	char			**shards;

	shards = ft_split(str, '*');
	if (!shards)
		return (NULL);
	dir = opendir(".");
	matches = NULL;
	size = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (is_matching(str, shards, entry->d_name))
		{
			if (!add_match(entry->d_name, &matches, &size))
				return (free_split(shards), free_split(matches),
					perror("minishell"), NULL);
		}
		entry = readdir(dir);
	}
	return (matches);
}
