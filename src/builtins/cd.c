/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:03:16 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/30 17:51:25 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	end_do_cd(char *path, char **env[])
{
	if (clean_path(&path))
		return (1);
	if (exec_cd(path))
		return (1);
	free(path);
	if (do_change_env(env))
		return (1);
	return (0);
}

static char	do_cd(char	*path, char **env[])
{
	char	*cpath;
	char	err;

	if (path[0] != '/' && path[0] != '.')
	{
		cpath = search_path(path, *env, "CDPATH");
		if (cpath != NULL)
		{
			free(path);
			path = cpath;
		}
	}
	else if (path[0] == '.')
	{
		err = add_pwd(&path, *env);
		if (err == 1)
			return (1);
		else if (err == 2)
		{
			if (do_change_env(env))
				return (1);
			return (0);
		}
	}
	return (end_do_cd(path, env));
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
