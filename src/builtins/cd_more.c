/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_more.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:08:22 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/30 18:04:14 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_dir(char *path, int i)
{
	struct stat	stat_info;
	char		*cpy;

	cpy = ft_strdup(path);
	cpy[i] = '\0';
	if (cpy == NULL)
		return (free(path), 0);
	if (access(path, X_OK) == 0)
	{
		if (stat(path, &stat_info))
		{
			perror("minishell");
			return (free(cpy), free(path), 0);
		}
		if ((stat_info.st_mode & S_IFMT) == S_IFDIR)
			return (free(cpy), 1);
	}
	free(path);
	free(cpy);
	return (0);
}

char	clean_path(char **path)
{
	int		i;

	i = 0;
	while ((*path)[i])
	{
		if ((ft_strnstr(&(*path)[i], "../", 3)
			|| (ft_strnstr(&(*path)[i], "..", 2) && (*path)[i + 1]
					&& !(*path)[i + 2])))
		{
			if (!check_dir(*path, i) || rm_prev_dir(path, &i))
				return (1);
		}
		else if (ft_strnstr(&(*path)[i], "./", 2))
		{
			if (rm_current_dir(path, &i, size_dir(&(*path)[i])))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

char	add_pwd(char **path, char **env)
{
	char	*pwd;
	char	*npath;

	pwd = get_pwd(env);
	if (pwd == NULL)
		return (exec_cd(*path), 2);
	if (pwd[ft_strlen(pwd) - 1] != '/')
	{
		npath = ft_strjoin(pwd, "/");
		if (npath == NULL)
			return (free(*path), 1);
		pwd = npath;
	}
	npath = ft_strjoin(pwd, *path);
	free(*path);
	if (npath == NULL)
		return (1);
	*path = npath;
	return (0);
}

char	do_change_env_pwd(char **env[], char *oldpwd, char *newpwd)
{
	char	*argv[3];
	int		err;

	argv[0] = "export";
	argv[2] = NULL;
	if (oldpwd)
		argv[1] = ft_strjoin("OLDPWD=", oldpwd);
	else
		argv[1] = ft_strjoin("PWD=", newpwd);
	if (argv[1] == NULL)
		return (free(newpwd), 1);
	err = builtin_export(argv, env);
	free(argv[1]);
	free(newpwd);
	return (err);
}

char	do_change_env(char **env[])
{
	char	*pwd;

	pwd = get_pwd(*env);
	if (pwd != NULL)
	{
		if (do_change_env_pwd(env, pwd, NULL))
			return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	if (do_change_env_pwd(env, NULL, pwd))
		return (1);
	return (0);
}
