/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:04:27 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/17 18:02:27 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	get_path_env(char **env, char ***paths)
{
	int	i;

	*paths = NULL;
	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H'
			&& env[i][4] == '=')
		{
			*paths = ft_split(&env[i][5], ':');
			if (*paths == NULL)
				return (1);
			break ;
		}
		i++;
	}
	if (*paths == NULL)
		return (2);
	return (0);
}

static char	*create_complete_path(char *path, char *cmd)
{
	char	*c_path;
	char	*tmp;

	if (path[ft_strlen(path) - 1] != '/')
		tmp = ft_strjoin(path, "/");
	else
		tmp = ft_strdup(path);
	if (tmp == NULL)
		return (NULL);
	c_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (c_path == NULL)
		return (NULL);
	return (c_path);
}

static char	check_access(char *path)
{
	struct stat	stat_info;

	if (access(path, X_OK) == 0)
	{
		if (stat(path, &stat_info))
		{
			perror("minishell");
			return (free(path), -1);
		}
		if ((stat_info.st_mode & S_IFMT) != S_IFDIR)
			return (1);
	}
	free(path);
	return (0);
}

char	*search_path(char *cmd, char **env)
{
	char		*path;
	char		**paths;
	char		err;
	int			i;

	err = get_path_env(env, &paths);
	if (err)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = create_complete_path(paths[i], cmd);
		if (path == NULL)
			return (free_strs(paths), NULL);
		err = check_access(path);
		if (err == -1)
			return (free_strs(paths), NULL);
		else if (err == 1)
			return (free_strs(paths), path);
		i++;
	}
	free_strs(paths);
	return (NULL);
}
