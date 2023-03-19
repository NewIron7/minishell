/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:49:34 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/17 18:07:15 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	set_on_cmd(t_parsing **tokens, int start)
{
	int	i;

	i = -1;
	while (++i < start)
		*tokens = (*tokens)->next;
}

static int	check_redirection(t_parsing *tokens, int start, int end)
{
	int	i;
	int	redirs;

	i = -1;
	redirs = 0;
	while ((end != -1 && ++i < end - start) || (end == -1 && tokens))
	{
		if (tokens->type == R_INPUT || tokens->type == R_OUTPUT
			|| tokens->type == R_DINPUT || tokens->type == R_DOUTPUT)
			redirs++;
		tokens = tokens->next;
	}
	return (redirs);
}

static char	set_fd_redirection(int *fd_in, int *fd_out, t_parsing *tokens,
	int redirs)
{
	while (redirs--)
	{
		while (!put_new_fd_redirec(tokens, fd_out, fd_in))
			tokens = tokens->next;
		tokens = tokens->next;
		if (*fd_out == -1 || *fd_in == -1)
			return (perror(tokens->content), 1);
		tokens = tokens->next;
	}
	return (0);
}

static char	get_args(t_parsing *tokens, int end, int start, char ***args)
{
	int	i;
	int	j;

	*args = malloc(sizeof(**args) * (ft_lstsize_parsing(tokens) + 1));
	if (*args == NULL)
		return (1);
	i = 0;
	j = 0;
	while ((end != -1 && i++ < end - start) || (end == -1 && tokens))
	{
		if (!(is_redirection(tokens) || is_redirection(tokens->prev)))
			(*args)[j++] = tokens->content;
		tokens = tokens->next;
	}
	(*args)[j] = NULL;
	return (0);
}

void	exec_simple_cmd(t_process *process, t_env *envp, int need_fork,
	t_list **pipeline)
{
	int			redir;
	char		**args;
	t_parsing	*tokens;
	int			builtin;

	args = NULL;
	tokens = process->tokens.tokens;
	set_on_cmd(&tokens, process->tokens.start);
	put_var_env(&tokens, envp->env, envp->code);
	redir = check_env_heredoc(tokens, process->tokens.end,
			process->tokens.start, *envp);
	if (redir)
		return ;
	if (tokens->type == LEFT_PAR)
		return (exec_subshell(process, &envp->env, pipeline));
	redir = check_redirection(tokens, process->tokens.start,
			process->tokens.end);
	if (redir)
	{
		if (set_fd_redirection(&process->infile, &process->outfile,
				tokens, redir))
			return ;
	}
	if (get_args(tokens, process->tokens.end, process->tokens.start, &args))
		return ;
	if (*args == NULL)
		return ;
	builtin = is_builtin(args);
	if (need_fork || !builtin)
	{
		process->pid = fork();
		if (process->pid == -1)
			return ;
		else if (!process->pid)
		{
			if (!builtin)
				exec_cmd(args, envp->env, process, pipeline);
			else
			{
				redir = exec_builtin(args, &envp->env, process, pipeline);
				free_all(process->tokens.tokens, envp->env, pipeline, args);
				exit(redir);
			}
		}
	}
	else
		process->status = exec_builtin(args, &envp->env, process, pipeline);
	free(args);
}
