/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:21:28 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/23 20:07:30 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	while (ft_isspace(*str))
		str++;
	if (*str)
		return (0);
	else
		return (1);
}

int	builtin_exit(char *const argv[], char *envp[])
{
	unsigned int	status;

	if (!argv)
		status = 0;
	else if (!is_num(*++argv))
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", *argv);
		status = 2;
	}
	else
	{
		if (*(argv + 1))
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: exit: too many arguments\n");
			return (EXIT_FAILURE);
		}
		else
			status = (unsigned char) ft_atoi(*argv);
	}
	ft_printf("exit\n");
	free_env(envp);
	exit(status);
}
