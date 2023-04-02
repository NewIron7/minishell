/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:19:32 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/02 11:09:10 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_newline(int newline, int fd)
{
	if (newline)
	{
		if (write(fd, "\n", 1) < 0)
		{
			perror("echo: write error");
			return (1);
		}
	}
	return (0);
}

int	builtin_echo(char *const argv[], int fd)
{
	int	newline;

	newline = 1;
	if (argv[1])
	{
		if (!(ft_strcmp(*++argv, "-n")))
		{
			newline = 0;
			argv++;
		}
		while (*argv)
		{
			if (write(fd, *argv, ft_strlen(*argv)) < 0)
				return (perror("echo: write error"), 1);
			if (*++argv)
			{
				if (write(fd, " ", 1) < 0)
					return (perror("echo: write error"), 1);
			}
		}
	}
	if (check_newline(newline, fd))
		return (1);
	return (0);
}
