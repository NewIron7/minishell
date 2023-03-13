/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:13:36 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/13 08:44:52 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*g_cpids;

int	main(void)
{
	char		**envp;

	if (!init_env(&envp))
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	main_loop(&envp);
	return (EXIT_SUCCESS);
}
