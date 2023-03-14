/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:21:28 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/14 04:39:19 by ddelhalt         ###   ########.fr       */
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

int	builtin_exit(char *argv[], char *envp[], t_parsing *pars, t_list **pipeline)
{
	unsigned int	status;

	ft_printf("exit\n");
	if (!argv || !argv[1])
		status = 0;
	else if (!is_num(argv[1]))
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", argv[1]);
		status = 2;
	}
	else
	{
		if (argv[2])
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: exit: too many arguments\n");
			return (EXIT_FAILURE);
		}
		else
			status = (unsigned char) ft_atoi(argv[1]);
	}
	free_all(pars, envp, pipeline, argv);
	exit(status);
}
