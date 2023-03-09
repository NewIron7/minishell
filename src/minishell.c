/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/10 00:00:31 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	sig_handler(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
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
	int			code;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	list_parsing = NULL;
	code = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			builtin_exit(NULL, *envp);
		signal(SIGINT, SIG_IGN);
		add_history(line);
		err_parsing = parser(line, &list_parsing, *envp, code);
		if (err_parsing == 1)
			malloc_err(list_parsing, line, *envp);
		if (ft_heredoc(list_parsing) == 0 && err_parsing == 0)
			code = eval_exec(subtokens_init(list_parsing, 0, 0, -1), envp);
		if (WIFSIGNALED(code))
			ft_printf("\n");
		free(line);
		ft_lstclear_parsing(list_parsing);
		signal(SIGINT, &sig_handler);
	}
}
