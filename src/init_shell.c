/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:48:07 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/29 15:29:49 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **envp[])
{
	if (isatty(STDIN_FILENO))
	{
		if (!init_env(envp))
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
	}
	else
		exit(0);
}
