/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/03 22:05:46 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	sig_handler(int sig)
{
	t_list	*cpids;

	if (*(int *) g_cpids->content == INTERACTIVE)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		cpids = g_cpids->next;
		while (cpids)
		{
			kill(*(int *) cpids->content, sig);
			cpids = cpids->next;
		}
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
	int		*heredocs;

	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, &sig_handler);
	list_parsing = NULL;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			builtin_exit(NULL, *envp);
		*(int *) g_cpids->content = EXEC;
		signal(SIGQUIT, &sig_handler);
		add_history(line);
		err_parsing = parser(line, &list_parsing, *envp);
		if (err_parsing == 1)
			malloc_err(list_parsing, line, *envp);
		print_list_parsing(list_parsing);
		//$? = eval_exec(list_parsing, 0, -1, *envp);
		heredocs = ft_heredoc(list_parsing);
		if (heredocs != NULL)
			eval_exec(list_parsing, 0, -1, *envp);
		free(line);
		ft_lstclear_parsing(list_parsing);
		signal(SIGQUIT, SIG_IGN);
		*(int *) g_cpids->content = INTERACTIVE;
	}
}
