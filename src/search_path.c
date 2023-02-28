/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 18:04:27 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/28 20:09:22 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/minishell.h"

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
	int 	i;

	*paths = NULL;
	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T' && env[i][3] == 'H'
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

	tmp = ft_strjoin(path, "/");
	if (tmp == NULL)
		return (NULL);
	c_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (c_path == NULL)
		return (free(tmp), NULL);
	return (c_path);
}

char	*search_path(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	char	err;
	int		i;
	struct stat	stat_info;

	err = get_path_env(env, &paths);
	if (err)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path = create_complete_path(paths[i], cmd);
		if (path == NULL)
			return (free_strs(paths), NULL);
		if (access(path, F_OK) == 0)
		{
			if (stat(path, &stat_info))
				return (free(path), free_strs(paths), NULL);
			if ((stat_info.st_mode & S_IFMT)  == S_IFDIR && access(path, X_OK))
				return (free(path), free_strs(paths), NULL);
			else
				return (free_strs(paths), path);
		}
		free(path);
		i++;
	}
	free_strs(paths);
	return (NULL);
}
/*
int	main(int argc, char **argv, char **env)
{
	char	*err;
	//char	**argv_cpy;

	(void)argc;
	//argv_cpy = cpy_strs(argc - 1, argv + 1);
	err = search_path(argv[1], env);
	printf("err:%s\n", err);
	free(err);
}*/
