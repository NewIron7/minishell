/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:03:16 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/30 18:34:46 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	do_search_path(char **path, char **env)
{
	char	*cpath;

	if ((*path)[0] != '/' && (*path)[0] != '.')
	{
		cpath = search_path(*path, env, "CDPATH");
		if (cpath != NULL)
		{
			free(*path);
			*path = cpath;
		}
		return (1);
	}
	return (0);
}

static char	end_do_cd(char *path, char **env[], char cdpath)
{
	if (clean_path(&path))
		return (1);
	if (exec_cd(path, cdpath))
		return (1);
	free(path);
	if (do_change_env(env))
		return (1);
	return (0);
}

static char	do_cd(char	*path, char **env[])
{
	char	cdpath;
	char	err[2];

	cdpath = 0;
	if (do_search_path(&path, *env))
		cdpath = 1;
	else if (path[0] == '.')
	{
		err[0] = add_pwd(&path, *env);
		if (err[0] == 1)
			return (1);
		else if (err[0] == 2)
		{
			if (do_change_env(env))
				return (1);
			return (0);
		}
	}
	return (end_do_cd(path, env, cdpath));
}

int	builtin_cd(char *const argv[], char **env[])
{
	char	*path;

	if (*++argv)
	{
		if (*(argv + 1))
			ft_printf_fd(2, "minishell: cd: too many arguments\n");
		else
		{
			path = ft_strdup(*argv);
			if (path == NULL || do_cd(path, env))
				return (perror("minishell: cd"), 1);
		}
	}
	return (0);
}
