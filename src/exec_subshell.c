/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:23:00 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/03 04:04:16 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parsing	*subshell_init(t_portion chunck, t_list **pipeline)
{
	t_parsing	*new_end;

	while (chunck.start != chunck.end)
	{
		if (chunck.start->type == RIGHT_PAR)
			new_end = chunck.start;
		chunck.start = chunck.start->next;
	}
	free_pipeline(pipeline);
	*pipeline = NULL;
	return (new_end);
}

static int	redirect_subshell(t_process *process)
{
	if (dup2(process->infile, STDIN_FILENO) == -1)
		return (0);
	if (dup2(process->outfile, STDOUT_FILENO) == -1)
		return (0);
	return (1);
}

static void	end_subshell(t_list **pipeline, t_parsing *parsing, t_env *envp)
{
	envp->code = get_shell_code(*pipeline);
	ft_lstclear_parsing(parsing);
	free_pipeline(pipeline);
	free_env(envp->env);
	exit(envp->code);
}

static char	prep_for_subshell(t_process *process, t_env *envp)
{
	int	redirs;

	if (check_env_heredoc(process->chunck, *envp))
		return (1);
	if (put_var_env(process->chunck, *envp))
		return (1);
	redirs = check_redirection(process->chunck);
	if (redirs && set_fd_redirect(&process->infile, &process->outfile,
			process->chunck.start, redirs))
		return (1);
	return (0);
}

void	exec_subshell(t_process *process, t_env *envp, t_list **pipeline)
{
	t_parsing	*new_end;
	int			redir;

	if (prep_for_subshell(process, envp))
		return ;
	process->pid = fork();
	if (process->pid == -1)
		return ;
	else if (!process->pid)
	{
		redir = redirect_subshell(process);
		new_end = subshell_init(process->chunck, pipeline);
		if (redir)
			eval_exec(process->parsing, set_portion(process->chunck.start->next, new_end), envp, pipeline);
		else
			perror("minishell");
		end_subshell(pipeline, *process->parsing, envp);
	}
}
