/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:25:19 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/14 20:17:14 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char *const argv[], char *envp[])
{
	int		i;
	char	*name_end;

	while (*++argv)
	{
		if (!ft_strchr(*argv, '='))
		{
			i = 0;
			while (envp[i])
			{
				name_end = ft_strchr(envp[i], '=');
				if (!ft_strncmp(*argv, envp[i], name_end - envp[i]))
				{
					free(envp[i]);
					envp[i] = envp[i + 1];
					while (envp[++i])
						envp[i] = envp[i + 1];
				}
				if (envp[i])
					i++;
			}
		}
	}
	return (0);
}
