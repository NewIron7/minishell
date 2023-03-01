/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/01 06:52:59 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	sig_handler(int sig)
{
	//kill(0, sig);
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	malloc_err(t_parsing *list_parsing, char *line, char **envp)
{
	if (list_parsing)
		ft_lstclear_parsing(list_parsing);
	free(line);
	free_env(envp);
	exit(EXIT_FAILURE);
}

void	main_loop(char **envp[])
{
	char		*line;
	t_parsing	*list_parsing;
	char		err_parsing;

	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	list_parsing = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			builtin_exit(NULL, *envp);
		add_history(line);
		err_parsing = parser(line, &list_parsing, *envp);
		if (err_parsing == 1)
			malloc_err(list_parsing, line, *envp);
		print_list_parsing(list_parsing);
		free(line);
		ft_lstclear_parsing(list_parsing);
	}
}
