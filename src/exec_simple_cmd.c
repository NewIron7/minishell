/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:49:34 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/24 12:47:14 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static	void	fork_exec_cmd(char **args, char **envp, t_process *process, t_list **pipeline)
{
	process->pid = fork();
	if (process->pid)
		return ;
	else
		exec_cmd(args, envp, process, pipeline);
}

static	void	fork_exec_builtin(char **args, char ***envp, t_process *process, t_list **pipeline)
{
	int	ret;

	process->pid = fork();
	if (process->pid)
		return ;
	else
	{
		ret = exec_builtin(args, envp, process, pipeline);
		free_all(process->tokens.tokens, *envp, pipeline, args);
		exit(ret);
	}
}

void	exec_simple_cmd(t_process *process, t_env *envp, int need_fork,
	t_list **pipeline)
{
	char		**args;
	t_parsing	*tokens;
	int			builtin;
	int			i;

	tokens = process->tokens.tokens;
	i = -1;
	while (++i < process->tokens.start)
		tokens = tokens->next;
	if (tokens->type == LEFT_PAR)
		return (exec_subshell(process, &envp->env, pipeline));
	if (!verif_simple_cmd(process, tokens, envp, &args))
		return ;
	builtin = is_builtin(args);
	if (!builtin)
		fork_exec_cmd(args, envp->env, process, pipeline);
	else if (need_fork)
		fork_exec_builtin(args, &envp->env, process, pipeline);
	else
		process->status = exec_builtin(args, &envp->env, process, pipeline);
	free(args);
}
