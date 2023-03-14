/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 08:48:07 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/13 09:47:35 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **envp[], struct termios *t_modes)
{
	if (isatty(STDIN_FILENO))
	{
		if (!init_env(envp))
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		tcgetattr(STDIN_FILENO, t_modes);
	}
	else
		exit(0);
}
