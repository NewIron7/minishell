/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:13:36 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/01 23:39:58 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*g_cpids;

int	main(void)
{
	char		**envp;

	if (!minishell_init(&envp))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	main_loop(&envp);
	return (EXIT_SUCCESS);
}
