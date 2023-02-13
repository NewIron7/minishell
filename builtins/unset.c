/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:25:19 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/13 22:33:54 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char *const argv[], char *envp[])
{
	int	i;

	while (*++argv)
	{
		i = 0;
		while (envp[i])
		{
			name_end = ft_strchr(envp[i], '=');
			if (!ft_strncmp(*argv, envp[i], name_end - *argv))
			{
				free(envp[i]);
				while (envp[i])
				{
					ft_memmove(envp[i], envp[i + 1], sizeof(char *));
					i++;
				}
			}
			if (envp[i])
				i++;
		}
	}
	return (0);
}
