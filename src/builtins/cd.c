/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:18:17 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/30 16:08:55 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	exec_cd(char *path)
{
	printf("curpath:%s\n", path);
	if (*path && chdir(path))
		return (free(path), 1);
	return (0);
}

static char	rm_current_dir(char **path, int *i, int size)
{
	int	x;
	char	*npath;

	printf("currentdir rm:%s, i=%d, siz:%d\n", *path, *i, size);
	if (*i > 0 && (*path)[*i - 1] != '/')
		return ((*i)++, 0);
	x = *i;
	(*path)[x] = '\0';
	x += size;
	npath = ft_strjoin(*path, &(*path)[x]);
	free(*path);
	if (npath == NULL)
		return (1);
	*path = npath;
	return (0);
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



static char	rm_prev_dir(char **path, int *i)
{
	int	x;
	int	size;

	if (*i == 0 || (*path)[*i - 1] != '/')
		return ((*i)++, 0);
	if (*i == 1 && (*path)[0] == '/')
		return ((*i)++, 0);
	x = *i - 2;
	printf("path = %s| x=%d\n", &(*path)[x], x);
	while (x >= 0 && (*path)[x] != '/')
		x--;
	x++;
	if (x == 0 && (*path)[0] == '/')
		return ((*i)++, 0);
	size = size_dir(&(*path)[x]);
	if (rm_current_dir(path, &x, size))
		return (1);
	size = size_dir(&(*path)[x]);
	if (rm_current_dir(path, &x, size))
		return (1);
	*i = x;
	return (0);
}

static char	clean_path(char **path)
{
	int		i;

	i = 0;
	while ((*path)[i])
	{
		printf("Current:%s, i=%d\n", &(*path)[i], i);
		if (ft_strnstr(&(*path)[i], "../", 3)
			|| (ft_strnstr(&(*path)[i], "..", 2) && (*path)[i + 1]
				&& !(*path)[i + 2]))
		{
			if (rm_prev_dir(path, &i))
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

static char *get_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PWD=", 4))
			return (&env[i][4]);
		i++;
	}
	return (NULL);
}

static char	add_pwd(char **path, char **env)
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

static char	do_change_env_pwd(char **env[], char *oldpwd, char *newpwd)
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

static char	do_change_env(char **env[])
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
	if (clean_path(&path))
		return (1);
	printf("After clean: %s\n", path);
	if (exec_cd(path))
		return (1);
	free(path);
	if (do_change_env(env))
		return (1);
	return (0);
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
