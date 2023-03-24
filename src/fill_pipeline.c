/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:12:32 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/24 16:42:59 by ddelhalt         ###   ########.fr       */
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

static void	goto_next_pipe(t_parsing **tokens, int *i, int end)
{
	while (*tokens && (*i < end || end == -1))
	{
		if ((*tokens)->type == PIPE)
			return ;
		else if ((*tokens)->type == LEFT_PAR)
		{
			while ((*tokens)->type != RIGHT_PAR)
			{
				*tokens = (*tokens)->next;
				(*i)++;
			}
		}
		*tokens = (*tokens)->next;
		(*i)++;
	}
}

void	fill_pipeline(t_subtokens tokens, t_list **pipeline)
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
			fd = pipeline_init_process(subtokens_init(tokens.tokens, tokens.start, 0, i), pipeline, fd, STDOUT_FILENO);
			if (fd < 0)
				return (fill_pipeline_err(pipeline));
			i++;
			cpy = cpy->next;
			tokens.start = i;
		}
		goto_next_pipe(&cpy, &i, tokens.end);
	}
	if (pipeline_init_process(subtokens_init(tokens.tokens, tokens.start, 0, tokens.end), pipeline, fd, 0) < 0)
		return (fill_pipeline_err(pipeline));
}
