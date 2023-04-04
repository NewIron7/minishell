/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:50:56 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/04 19:26:57 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	expand_redirect(t_parsing *elem, t_env envp)
{
	(void) elem;
	(void) envp;
	return (0);
	/*
	t_expand	*split;
	t_list		*block;

	if (!split_quotes(&split, elem->content))
		return (EXIT_FAILURE);
	if (expand_var(split, envp))
		return (EXIT_FAILURE);	
	if (!split_fields(split, &block))
		return (EXIT_FAILURE);
	//if (!expand_wildcards(block))
		//return (EXIT_FAILURE);
	if (replace_content(block, elem))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
	*/
}

static int	expand_argument(t_parsing *elem, t_env envp)
{
	t_expand	*split;
	t_list		*block;

	if (!split_quotes(&split, elem->content))
		return (EXIT_FAILURE);
	if (expand_var(split, envp))
		return (EXIT_FAILURE);	
	if (!split_fields(split, &block))
		return (EXIT_FAILURE);
	//if (!expand_wildcards(block))
		//return (EXIT_FAILURE);
	if (replace_content(block, elem))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	put_var_env(t_portion chunck, t_env envp)
{
	t_parsing	*next;
	int			err;

	err = 0;
	while (chunck.start != chunck.end)
	{
		next = chunck.start->next;
		if (chunck.start->type == LEFT_PAR)
		{
			chunck.start = goto_par_end(chunck.start);
			next = chunck.start->next;
		}
		else if (chunck.start->prev && is_redirect(chunck.start->prev))
			err = expand_redirect(chunck.start, envp);
		else if (chunck.start->type == CMD || chunck.start->type == ARG)
			err = expand_argument(chunck.start, envp);
		if (err)
			return (err);
		chunck.start = next;
	}
	return (0);
}
