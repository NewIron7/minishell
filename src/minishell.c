/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 09:55:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/14 18:04:17 by hboissel         ###   ########.fr       */
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

int	get_shell_code(t_list *pipeline)
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
	int			code;
	char		**envp;
	t_list		*pipeline;

	init_shell(&envp);
	list_parsing = NULL;
	code = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			builtin_exit(NULL, envp, NULL, NULL);
		add_history(line);
		if (*line)
		{
			signal(SIGINT, SIG_IGN);
			code = parser(line, &list_parsing, envp, code);
			//print_list_parsing(list_parsing);
			put_var_env(&list_parsing, envp, code);
			free(line);
			if (!code && ft_heredoc(list_parsing) == 0)
			{
				eval_exec(subtokens_init(list_parsing, 0, 0, -1), &envp, &pipeline);
				code = get_shell_code(pipeline);
				free_pipeline(&pipeline);
			}
			ft_lstclear_parsing(list_parsing);
			signal(SIGINT, &sig_handler);
		}
		else
			free(line);
	}
}
