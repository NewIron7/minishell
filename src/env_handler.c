/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:08:27 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/13 08:43:18 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

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
