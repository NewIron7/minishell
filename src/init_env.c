/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:08:27 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/14 03:59:53 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(char	**envp[])
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	*envp = calloc(i + 1, sizeof(char *));
	if (!*envp)
		return (0);
	i = 0;
	while (environ[i])
	{
		(*envp)[i] = ft_strdup(environ[i]);
		if (!(*envp)[i])
		{
			free_env(*envp);
			*envp = NULL;
			return (0);
		}
		i++;
	}
	return (1);
}
