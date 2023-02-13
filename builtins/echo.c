/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:19:32 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/13 22:32:52 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char *const argv[])
{
	int	newline;

	newline = 1;
	if (!(ft_strcmp(++*argv, "-n")))
	{
		newline = 0;
		argv++;
	}
	while (*argv)
	{
		ft_printf("%s", *argv);
		if (*++argv)
			ft_printf("%c", ' ');
	}
	if (newline)
		ft_printf("%c", '\n');
	return (0);
}
