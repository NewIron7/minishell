/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:12:32 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 09:11:34 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipeline_close(t_list **pipeline)
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

static void	fill_pipeline_err(t_list **pipeline)
{
	pipeline_close(pipeline);
	ft_lstclear(pipeline, &free);
	*pipeline = NULL;
}

static t_parsing	*goto_next_pipe(t_parsing *elem, t_parsing *end)
{
	while (elem != end)
	{
		if (elem->type == PIPE)
			return (elem);
		else if (elem->type == LEFT_PAR)
			elem = goto_par_end(elem);
		elem = elem->next;
	}
	return (elem);
}

static void	fill_pipeline_parsing(t_parsing **parsing, t_list *pipeline)
{
	t_process	*process;

	while (pipeline)
	{
		process = pipeline->content;
		process->parsing = parsing;
		pipeline = pipeline->next;
	}
}

void	fill_pipeline(t_parsing **parsing, t_portion chunck, t_list **pipeline)
{
	t_parsing	*cpy;
	t_parsing	*start;
	int			fd;

	cpy = chunck.start;
	start = chunck.start;
	fd = STDIN_FILENO;
	while (cpy != chunck.end)
	{
		if (cpy->type == PIPE)
		{
			fd = pipeline_init_process(set_portion(start, cpy),
					pipeline, fd, 1);
			if (fd < 0)
				return (fill_pipeline_err(pipeline));
			cpy = cpy->next;
			start = cpy;
		}
		cpy = goto_next_pipe(cpy, chunck.end);
	}
	if (pipeline_init_process(set_portion(start, cpy), pipeline, fd, 0) < 0)
		return (fill_pipeline_err(pipeline));
	fill_pipeline_parsing(parsing, *pipeline);
}
