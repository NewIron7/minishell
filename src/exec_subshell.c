/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:23:00 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/24 15:42:58 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	subshell_init(t_process *process, t_subtokens *tokens, t_parsing **cpy, t_list **pipeline)
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

void	exec_subshell(t_process *process, t_env *envp, t_list **pipeline)
{
	int			new_end;
	t_parsing	*cpy;
	t_subtokens	tokens;

	process->pid = fork();
	if (process->pid == -1)
		return ;
	else if (!process->pid)
	{
		new_end = subshell_init(process, &tokens, &cpy, pipeline);
		eval_exec(subtokens_init(tokens.tokens, tokens.start + 1, 0, new_end - 1), envp, pipeline);
		ft_lstclear_parsing(tokens.tokens);
		free_pipeline(pipeline);
		free_env(envp->env);
		exit(envp->code);
	}
}
