/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 05:23:00 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/02 11:28:41 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	subshell_init(t_process *process, t_subtokens *tokens,
	t_parsing **cpy, t_list **pipeline)
{
	int	i;
	int	new_end;

	*tokens = process->tokens;
	*cpy = tokens->tokens;
	i = -1;
	while (++i < tokens->start)
		*cpy = (*cpy)->next;
	while (*cpy && (i < tokens->end || tokens->end == -1))
	{
		if ((*cpy)->type == RIGHT_PAR)
			new_end = i + 1;
		*cpy = (*cpy)->next;
		i++;
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

static void	end_subshell(t_list **pipeline, t_subtokens tokens, t_env *envp)
{
	envp->code = get_shell_code(*pipeline);
	free_pipeline(pipeline);
	ft_lstclear_parsing(tokens.tokens);
	free_env(envp->env);
	exit(envp->code);
}

static char	prep_for_subshell(t_process *process, t_env *envp)
{
	int	redirs;

	if (check_env_heredoc(process->tokens.tokens, process->tokens.end,
			process->tokens.start, *envp))
		return (1);
	redirs = check_redirection(process->tokens.tokens, process->tokens.start,
			process->tokens.end);
	if (redirs && set_fd_redirect(&process->infile, &process->outfile,
			process->tokens.tokens, redirs))
		return (1);
	return (0);
}

void	exec_subshell(t_process *process, t_env *envp, t_list **pipeline)
{
	int			new_end;
	t_parsing	*cpy;
	t_subtokens	tokens;
	int			redir;

	if (prep_for_subshell(process, envp))
		return ;
	process->pid = fork();
	if (process->pid == -1)
		return ;
	else if (!process->pid)
	{
		redir = redirect_subshell(process);
		new_end = subshell_init(process, &tokens, &cpy, pipeline);
		if (redir)
			eval_exec(subtokens_init(tokens.tokens, tokens.start + 1, 0,
					new_end - 1), envp, pipeline);
		else
			perror("minishell");
		end_subshell(pipeline, tokens, envp);
	}
}
