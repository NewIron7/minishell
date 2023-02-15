/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/15 11:20:55 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(char **envp[])
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			builtin_exit(NULL, *envp);
		ft_printf("%s\n", line);
		free(line);
	}
}
