/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:23:00 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/30 14:09:51 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	subshell_init(t_process *process, t_subtokens *tokens,
	t_parsing **cpy, t_list **pipeline)
{
	int	i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	*tokens = process->tokens;
	*cpy = tokens->tokens;
	i = -1;
	while (++i < tokens->start)
		*cpy = (*cpy)->next;
	while (*cpy && (i < tokens->end || tokens->end == -1))
	{
		*cpy = (*cpy)->next;
		i++;
	}
	free_pipeline(pipeline);
	*pipeline = NULL;
	return (i);
}

static int	get_exit_status(t_list *pipeline)
{
	t_process	*process;

	while (pipeline)
	{
		process = pipeline->content;
		if (process->killed && get_status(process->status) == SIGINT)
			return (process->status);
		pipeline = pipeline->next;
	}
	return (process->status);
}

void	exec_subshell(t_process *process, t_env *envp, t_list **pipeline)
{
	int			new_end;
	t_parsing	*cpy;
	t_subtokens	tokens;
	int			status;

	process->pid = fork();
	if (process->pid == -1)
		return ;
	else if (!process->pid)
	{
		new_end = subshell_init(process, &tokens, &cpy, pipeline);
		eval_exec(subtokens_init(tokens.tokens, tokens.start + 1, 0,
				new_end - 1), envp, pipeline);
		ft_lstclear_parsing(tokens.tokens);
		status = get_exit_status(*pipeline);
		free_pipeline(pipeline);
		free_env(envp->env);
		exit(status);
	}
}
