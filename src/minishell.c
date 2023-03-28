/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 16:48:20 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	sig_handler(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

int	get_shell_code(t_list *pipeline)
{
	t_process	*process;

	pipeline = ft_lstlast(pipeline);
	process = pipeline->content;
	if (!process->pid || process->pid == -1)
		return (process->status);
	if (WIFEXITED(process->status))
		return (WEXITSTATUS(process->status));
	else if (WIFSIGNALED(process->status))
		return (WTERMSIG(process->status) + 128);
	else
		return (EXIT_FAILURE);
}

static t_env	process_line(char *line, t_parsing **parsing,
	t_list **pipeline, t_env envp)
{
	char	err;

	signal(SIGINT, SIG_IGN);
	err = parser(line, parsing);
	if (err == 2)
		envp.code = 2;
	free(line);
	if (!err && ft_heredoc(*parsing) == 0)
	{
		eval_exec(subtokens_init(*parsing, 0, 0, -1), &envp, pipeline);
		free_pipeline(pipeline);
	}
	ft_lstclear_parsing(*parsing);
	signal(SIGINT, &sig_handler);
	return (envp);
}

void	main_loop(void)
{
	char		*line;
	t_parsing	*list_parsing;
	t_env		envp;
	t_list		*pipeline;

	init_shell(&envp.env);
	list_parsing = NULL;
	envp.code = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			builtin_exit(NULL, envp.env, NULL, NULL);
		add_history(line);
		if (*line)
			envp = process_line(line, &list_parsing, &pipeline, envp);
		else
			free(line);
	}
}
