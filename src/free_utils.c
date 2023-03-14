/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:41:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/14 04:04:56 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**free_pipeline(t_list **pipeline)
{
	ft_lstclear(pipeline, &free);
	*pipeline = NULL;
	return (pipeline);
}

void	free_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	free_all(t_parsing *pars, char *envp[], t_list **pipeline, char **args)
{
	if (pars)
		ft_lstclear_parsing(pars);
	if (envp)
		free_env(envp);
	if (pipeline)
		free_pipeline(pipeline);
	if (args)
		free(args);
}
