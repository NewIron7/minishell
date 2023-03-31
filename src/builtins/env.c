/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:22:27 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/31 15:54:26 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char *const envp[], int fd)
{
	while (*envp)
	{
		if (write(fd, *envp, ft_strlen(*envp)) < 0 || write(fd, "\n", 1) < 0)
		{
			perror("env: write error");
			return (1);
		}
		envp++;
	}
	return (0);
}
