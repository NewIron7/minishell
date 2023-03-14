/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:38:04 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/14 01:44:06 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipeline_init_process(t_subtokens tokens, t_list **pipeline, int infile, int outfile)
{
	t_process	*process;
	t_list		*lst;
	int			pipe_fd[2];

	process = malloc(sizeof(t_process));
	if (!process)
		return (-1);
	process->tokens = tokens;
	process->pid = 0;
	process->killed = 0;
	process->status	= 0;
	process->infile = infile;
	pipe_fd[0] = STDIN_FILENO;
	process->outfile = STDOUT_FILENO;
	if (outfile)
	{
		if (pipe(pipe_fd) == -1)
		{
			free(process);
			return (-1);
		}
		process->outfile = pipe_fd[1];
	}
	lst = ft_lstnew(process);
	if (!lst)
	{
		free(process);
		return (-1);
	}
	ft_lstadd_back(pipeline, lst);
	return (pipe_fd[0]);
}

static void pipeline_close(t_list **pipeline)
{
	t_process	*process;
	t_list		*lst;

	lst = *pipeline;
	while (lst)
	{
		process = lst->content;
		if (process->infile != STDIN_FILENO)
			close(process->infile);
		if (process->outfile != STDOUT_FILENO)
			close(process->outfile);
		lst = lst->next;
	}
}

static void killed_printer(t_list *pipeline)
{
	t_process	*process;

	if (is_pipeline_sigint(pipeline))
		ft_printf_fd(2, "\n");
	else
	{
		pipeline = ft_lstlast(pipeline);
		process = pipeline->content;
		if (process->killed && get_status(process->status) == SIGQUIT)
			ft_printf_fd(2, "Quit (core dumped)\n");
		else if (process->killed && get_status(process->status) == SIGTERM)
			ft_printf_fd(2, "Terminated\n");
		else if (process->killed)
			ft_printf_fd(2, "\n");
	}
}

static void	fill_pipeline(t_subtokens tokens, t_list **pipeline)
{
	int			i;
	t_parsing	*cpy;
	int			fd;

	i = -1;
	cpy = tokens.tokens;
	fd = STDIN_FILENO;
	while (++i < tokens.start)
		cpy = cpy->next;
	while (cpy && (i < tokens.end || tokens.end == -1))
	{
		if (cpy->type == PIPE)
		{
			fd = pipeline_init_process(subtokens_init(tokens.tokens, tokens.start, 0, i), pipeline, fd, 1);
			if (fd < 0)
			{
				pipeline_close(pipeline);
				ft_lstclear(pipeline, &free);
				*pipeline = NULL;
				return ;
			}
			i++;
			cpy = cpy->next;
			tokens.start = i;
		}
		else if (cpy->type == LEFT_PAR)
		{
			while (cpy->type != RIGHT_PAR)
			{
				cpy = cpy->next;
				i++;
			}
		}
		cpy = cpy->next;
		i++;
	}
	if (pipeline_init_process(subtokens_init(tokens.tokens, tokens.start, 0, tokens.end), pipeline, fd, 0) < 0)
	{
		pipeline_close(pipeline);
		ft_lstclear(pipeline, &free);
		*pipeline = NULL;
	}
}

void	wait_pipeline(t_list **pipeline)
{
	t_list		*cpy;
	t_process	*process;

	cpy = *pipeline;
	while (cpy)
	{
		process = cpy->content;
		if (process->pid)
		{
			waitpid(process->pid, &process->status, 0);
			if (WIFSIGNALED(process->status))
				process->killed = 1;
		}
		cpy = cpy->next;
	}
}

void	exec_pipeline(t_subtokens tokens, char **envp[], t_list **pipeline)
{
	t_list		*cpy;
	t_process	*process;

	fill_pipeline(tokens, pipeline);
	if (!*pipeline)
	{
		perror("minishell");
		return ;
	}
	if (!(*pipeline)->next)
	{
		process = (*pipeline)->content;
		exec_simple_cmd(process, envp, 0);
		if (process->infile != STDIN_FILENO)
			close(process->infile);
		if (process->outfile != STDOUT_FILENO)
			close(process->outfile);
	}
	else
	{
		cpy = *pipeline;
		while (cpy)
		{
			process = cpy->content;
			exec_simple_cmd(process, envp, 1);
			if (process->infile != STDIN_FILENO)
				close(process->infile);
			if (process->outfile != STDOUT_FILENO)
				close(process->outfile);
			cpy = cpy->next;
		}
	}
	wait_pipeline(pipeline);
	killed_printer(*pipeline);
}
