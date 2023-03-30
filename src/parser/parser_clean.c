/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:26:57 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/30 19:53:14 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	check_par_around(int current, t_parsing *list_parsing)
{
	if (list_parsing)
	{
		if (list_parsing->type == current)
			return (1);
	}
	return (0);
}

static char	check_parsing_par(int current, t_parsing *list_parsing)
{
	t_parsing	*next;

	next = list_parsing->next;
	if (current == RIGHT_PAR
		&& !((is_redirect(next) || is_and_pipe_or(next) || !next
				|| check_par_around(current, list_parsing->next))
			&& (is_cmd_arg(list_parsing->prev)
				|| check_par_around(current, list_parsing->prev))))
		return (syntax_error_near(list_parsing->content));
	if (current == LEFT_PAR
		&& !((is_cmd_arg(next) || is_redirect(next)
				|| check_par_around(current, list_parsing->next))
			&& (is_and_pipe_or(list_parsing->prev)
				|| !list_parsing->prev
				|| check_par_around(current, list_parsing->prev))))
		return (syntax_error_near(list_parsing->content));
	return (0);
}

static char	verif_par(t_parsing *list_parsing)
{
	int			nb[3];
	t_parsing	*next;
	char		err;

	nb[0] = 0;
	nb[1] = 0;
	while (list_parsing)
	{
		nb[2] = list_parsing->type;
		if (nb[2] == LEFT_PAR || nb[2] == RIGHT_PAR)
		{
			if (nb[2] == LEFT_PAR)
				nb[0]++;
			else
				nb[1]++;
			err = check_parsing_par(nb[2], list_parsing);
			if (err)
				return (err);
		}
		next = list_parsing;
		list_parsing = list_parsing->next;
	}
	if (nb[0] != nb[1])
		return (syntax_error_near(next->content));
	return (0);
}

static char	verif_redirect(t_parsing *list_parsing)
{
	char	*content;

	while (list_parsing)
	{
		if (list_parsing->type == REDIRECT_TMP)
		{	
			content = list_parsing->content;
			if (!list_parsing->next || list_parsing->next->type == REDIRECT_TMP)
				return (syntax_error_near(list_parsing->content));
			if (!ft_strcmp_parsing(content, "<"))
				list_parsing->type = R_INPUT;
			else if (!ft_strcmp_parsing(content, ">"))
				list_parsing->type = R_OUTPUT;
			else if (!ft_strcmp_parsing(content, "<<"))
				list_parsing->type = R_DINPUT;
			else if (!ft_strcmp_parsing(content, ">>"))
				list_parsing->type = R_DOUTPUT;
			else
				return (syntax_error_near(list_parsing->content));
		}
		list_parsing = list_parsing->next;
	}
	return (0);
}

char	list_parsing_clean(t_parsing *list_parsing)
{
	if (verif_pipe(list_parsing))
		return (1);
	if (verif_redirect(list_parsing))
		return (1);
	if (verif_and(list_parsing))
		return (1);
	if (verif_par_tmp(list_parsing))
		return (1);
	if (verif_par(list_parsing))
		return (1);
	return (0);
}
