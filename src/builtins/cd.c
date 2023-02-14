/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:18:17 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/14 19:08:42 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char *const argv[])
{
	if (*++argv)
	{
		if (*(argv + 1))
			ft_printf_fd(2, "minishell: cd: too many arguments\n");
		else if (chdir(*argv))
		{
			perror("minishell: cd");
			return (1);
		}
	}
	return (0);
}
