/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:49:34 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/03 03:31:51 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static	void	fork_exec_cmd(char **args, char **envp, t_process *process,
	t_list **pipeline)
{
	process->pid = fork();
	if (process->pid)
		return ;
	else
		exec_cmd(args, envp, process, pipeline);
}

static	void	fork_exec_builtin(char **args, t_env *envp, t_process *process,
	t_list **pipeline)
{
	int	ret;

	process->pid = fork();
	if (process->pid)
		return ;
	else
	{
		ret = exec_builtin(args, envp, process, pipeline);
		free_all(*process->parsing, envp->env, pipeline, args);
		exit(ret);
	}
}

void	exec_simple_cmd(t_process *process, t_env *envp, t_list **pipeline)
{
	char		**args;
	int			builtin;

	if (process->chunck.start->type == LEFT_PAR)
		return (exec_subshell(process, envp, pipeline));
	if (!verif_simple_cmd(process, envp, &args))
	{
		process->status = EXIT_FAILURE;
		return ;
	}
	builtin = is_builtin(args);
	if (!builtin)
		fork_exec_cmd(args, envp->env, process, pipeline);
	else if (process->to_fork)
		fork_exec_builtin(args, envp, process, pipeline);
	else
		process->status = exec_builtin(args, envp, process, pipeline);
	free(args);
}
