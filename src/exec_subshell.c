/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:23:00 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/14 06:52:10 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_subshell(t_process *process, char **envp[], t_list **pipeline)
{
	t_list	*sub_pipeline;
	int		code;
	int		i;
	t_parsing	*cpy;

	process->pid = fork();
	if (process->pid == -1)
		return ;
	else if (!process->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		sub_pipeline = NULL;
		cpy = process->tokens.tokens;
		i = -1;
		while (++i < process->tokens.start)
			cpy = cpy->next;
		while (cpy && (i < process->tokens.end || process->tokens.end == -1))
		{
			cpy = cpy->next;
			i++;
		}
		eval_exec(subtokens_init(process->tokens.tokens, process->tokens.start + 1, 0, i - 1), envp, &sub_pipeline);
		code = get_shell_code(sub_pipeline);
		ft_lstclear_parsing(process->tokens.tokens);
		free_pipeline(&sub_pipeline);
		free_pipeline(pipeline);
		free_env(*envp);
		exit(code);
	}
}
