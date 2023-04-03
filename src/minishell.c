/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/03 04:05:35 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern int	g_fd;

void	sig_handler(int sig)
{
	(void) sig;
	ft_printf_fd(1, "\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	g_fd = -2;
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
	char	*tmp;

	tmp = ft_strtrim(line, " \n\t");
	free(line);
	if (!tmp)
		return (perror("minishell"), envp.code = 1, envp);
	line = tmp;
	if (!*line)
		return (free(line), envp);
	err = parser(line, parsing);
	if (err == 2)
		envp.code = 2;
	free(line);
	if (!err && ft_heredoc(*parsing) == 0)
	{
		eval_exec(parsing, set_portion(*parsing, NULL), &envp, pipeline);
		free_pipeline(pipeline);
	}
	ft_lstclear_parsing(*parsing);
	return (envp);
}

void	check_ctrl_c(int *code)
{
	if (g_fd == -2)
	{
		*code = 130;
		g_fd = -1;
	}
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
		signal(SIGINT, SIG_IGN);
		if (!line)
		{
			ft_printf("exit\n");
			builtin_exit(NULL, envp, NULL, NULL);
		}
		add_history(line);
		check_ctrl_c(&envp.code);
		if (*line)
			envp = process_line(line, &list_parsing, &pipeline, envp);
		else
			free(line);
		signal(SIGINT, &sig_handler);
	}
}
