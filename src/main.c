/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:13:36 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/15 11:24:32 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	extern char	**environ;
	char		**envp;

	envp = init_env(environ);
	if (!envp)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	main_loop(&envp);
	return (EXIT_SUCCESS);
}
