/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:19:32 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 17:42:32 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			{
				perror("echo: write error");
				return (1);
			}
			if (*++argv)
				ft_printf_fd(fd, "%c", ' ');
		}
	}
	if (newline)
		ft_printf_fd(fd, "%c", '\n');
	return (0);
}
