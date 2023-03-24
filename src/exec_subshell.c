/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:23:00 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/24 10:47:42 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_subshell(t_process *process, char **envp[], t_list **pipeline)
{
	t_list	*sub_pipeline;
	int		i;
	t_env	sub_env;
	t_parsing	*cpy;
	t_subtokens	sub_tokens;

	sub_env.env = *envp;
	sub_env.code = 0;
	process->pid = fork();
	sub_tokens = process->tokens;
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
		free_pipeline(pipeline);
		eval_exec(subtokens_init(sub_tokens.tokens, sub_tokens.start + 1, 0, i - 1), &sub_env, &sub_pipeline);
		ft_lstclear_parsing(sub_tokens.tokens);
		free_pipeline(&sub_pipeline);
		free_env(*envp);
		exit(sub_env.code);
	}
}
