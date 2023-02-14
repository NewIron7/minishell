/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:23:31 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/13 22:33:41 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*curpath;

	curpath = getcwd(NULL, 0);
	if (!curpath)
	{
		perror("minishell: pwd");
		return (EXIT_FAILURE);
	}
	else
		ft_printf("%s\n", curpath);
	free(curpath);
	return (0);
}
