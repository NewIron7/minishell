/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 23:18:13 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/01 23:45:32 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_g_cpids(void)
{
	int	*mode;

	g_cpids = NULL;
	mode = malloc(sizeof(int));
	if (!mode)
		return ;
	*mode = INTERACTIVE;
	g_cpids = ft_lstnew(mode);
	if (!g_cpids)
		free(mode);
}

int	minishell_init(char **envp[])
{
	init_g_cpids();
	if (!g_cpids)
		return (0);
	init_env(envp);
	if (!envp)
	{
		ft_lstclear(&g_cpids, &free);
		return (0);
	}
	return (1);
}
