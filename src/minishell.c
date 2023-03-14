/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/14 01:24:30 by ddelhalt         ###   ########.fr       */
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

static int	get_shell_code(t_list *pipeline)
{
	t_process	*process;

	pipeline = ft_lstlast(pipeline);
	process = pipeline->content;
	if (WIFEXITED(process->status))
		return (WEXITSTATUS(process->status));
	else if (WIFSIGNALED(process->status))
		return (WTERMSIG(process->status) + 128);
	else
		return (EXIT_FAILURE);
}

void	main_loop(void)
{
	char		*line;
	t_parsing	*list_parsing;
	char		err_parsing;
	int			code;
	char		**envp;
	struct termios	t_modes;
	t_list		*pipeline;

	init_shell(&envp, &t_modes);
	list_parsing = NULL;
	code = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			builtin_exit(NULL, envp);
		signal(SIGINT, SIG_IGN);
		add_history(line);
		err_parsing = parser(line, &list_parsing, envp, code);
		if (err_parsing == 1)
			malloc_err(list_parsing, line, envp);
		if (ft_heredoc(list_parsing) == 0 && err_parsing == 0)
			eval_exec(subtokens_init(list_parsing, 0, 0, -1), &envp, &pipeline);
		code = get_shell_code(pipeline);
		free(line);
		ft_lstclear_parsing(list_parsing);
		signal(SIGINT, &sig_handler);
	}
}
