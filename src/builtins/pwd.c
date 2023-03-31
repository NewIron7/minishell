/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:23:31 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/31 15:54:02 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(int fd)
{
	char	*curpath;

	curpath = getcwd(NULL, 0);
	if (!curpath)
	{
		perror("minishell: pwd");
		return (EXIT_FAILURE);
	}
	else
	{
		if (write(fd, curpath, ft_strlen(curpath)) < 0 || write(fd, "\n", 1) < 0)
		{
			perror("pwd: write error");
			free(curpath);
			return (1);
		}
	}
	free(curpath);
	return (0);
}
