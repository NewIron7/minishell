/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pid_glob.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 09:19:51 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/02 09:27:39 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_pid_glob(int pid)
{
	int		*content;
	t_list	*new;

	content = malloc(sizeof(int));
	if (!content)
		return (0);
	*content = pid;
	new = ft_lstnew(content);
	if (!new)
	{
		free(content);
		return (0);
	}
	ft_lstaddback(&g_cpids, new);
	return (1);
}
