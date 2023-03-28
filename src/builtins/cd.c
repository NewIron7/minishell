/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:18:17 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 19:28:42 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	exec_cd(char *path)
{
	if (chdir(path))
		return (perror("minishell: cd"), 1);
	return (0);
}

static char	*rm_prev_dir(char *path, int *i)
{
	char	*npath;
	int		x;

	x = *i - 2;
	if (path[i - 1] != '/')
		return (path);
	while (x >= 0 && path[x] != '/')
		x--;
	if (x < 0)
		path[0] = '\0';
	else
		path[x] = '\0';
	if (ft_strnstr(&path[x + 1], "root/", 5) || ft_strnstr(&path[x + 1], "../", 3))
		return (path[x] = '/', path);
	cpath = ft_strjoin(path, &path[i]);
	if (cpath == NULL)
		return (1);
	return (cpath);
}

static char	*rm_current_dir(char *path, int *i, int size)
{
	int	x;
	char	*npath;

	x = *i;
	*i += size;
	path[x] = 0;
	x += size;
	npath = ft_strjoin(path, &path[x]);
	if (npath == NULL)
		return (1);
	free(path);
	return (npath);
}

static int	size_dir(char *path)
{
	int	size;

	size = 0;
	while (path[size] && path[size] != '/')
		size++;
	if (path[size] == '/')
		size++;
	return (size);
}

static char	*clean_path(char *path)
{
	int		i;
	char	*err;

	i = 0;
	while (path[i])
	{
		if (ft_strnstr(path, "/..", 3))
		{
			err = rm_prev_dir(path, &(++i));
			if (err == NULL)
				return (free(path), 1);
			err = rm_current_dir(err, &i, size_dir(&path[i]));
			if (err == NULL)
				return (free(path), 1);
			free(path);
			path = err;
		}
		else if (ft_strnstr(path, "./", 2))
		{
			err = rm_current_dir(err, &i, size_dir(&path[i]));
			if (err == NULL)
				return (free(path), 1);
			free(path);
			path = err;
		}
		i++;
	}
	return (path)
}

static void	do_cd(char	*path, char **env)
{
	char	*cpath;

	if (path[0] != '/' && path[0] != '.')
		cpath = search_path(path, env, "CDPATH");
	if (cpath)
		path = clean_path(cpath);
	else
		path = clean_path(path);
}

int	builtin_cd(char *const argv[], char **env)
{
	if (*++argv)
	{
		if (*(argv + 1))
			ft_printf_fd(2, "minishell: cd: too many arguments\n");
		else if (chdir(*argv))
		{
			perror("minishell: cd");
			return (1);
		}
	}
	return (0);
}
