/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:04:06 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/30 17:06:04 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_dir(char *path)
{
	int	size;

	size = 0;
	while (path[size] && path[size] != '/')
		size++;
	if (path[size] == '/')
		size++;
	return (size);
}

char	*get_pwd(char **env)
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

char	exec_cd(char *path)
{
	if (*path && chdir(path))
		return (free(path), 1);
	return (0);
}

char	rm_current_dir(char **path, int *i, int size)
{
	int		x;
	char	*npath;

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

char	rm_prev_dir(char **path, int *i)
{
	int	x;
	int	size;

	if (*i == 0 || (*path)[*i - 1] != '/')
		return ((*i)++, 0);
	if (*i == 1 && (*path)[0] == '/')
		return ((*i)++, 0);
	x = *i - 2;
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
