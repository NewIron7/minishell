/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/15 11:58:31 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(char **envp[])
{
	char	*line;
	t_parsing	*list_parsing;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			builtin_exit(NULL, *envp);
		add_history(line);
		ft_printf("///ROW\\\\\\\n");
		ft_printf("%s\n", line);
		parser(line, &list_parsing, *envp);
		ft_printf("///PARSING\\\\\\\n");
		print_list_parsing(list_parsing);
		free(line);
	}
}
