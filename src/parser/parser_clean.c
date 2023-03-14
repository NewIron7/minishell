/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:26:57 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/14 01:50:05 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	syntax_error_near(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
	return (2);
}

static char	ft_strcmp_parsing(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 != *str2)
		return (1);
	return (0);
}

static char		is_unvalid_next_token(t_parsing *tokens)
{
	char	next;

	if (tokens && tokens->next)
	{
		next = tokens->next->type;
		if (next == AND || next == OR || next == PIPE)
			return (1);
		return (0);
	}
	return (1);
}

static char    verif_and(t_parsing *list_parsing)
{
	while (list_parsing)
	{
		if (list_parsing->type == AND)
		{
			if (is_unvalid_next_token(list_parsing) || ft_strcmp_parsing(list_parsing->content, "&&"))
				return (syntax_error_near(list_parsing->content));
		}
		list_parsing = list_parsing->next;
	}
	return (0);
}

static char	verif_pipe(t_parsing *list_parsing)
{
	while (list_parsing)
	{
		if (list_parsing->type == PIPE)
		{
			if (!ft_strcmp_parsing(list_parsing->content, "||"))
				list_parsing->type = OR;
			if (is_unvalid_next_token(list_parsing)
					|| (ft_strcmp_parsing(list_parsing->content, "|") && list_parsing->type != OR))
				return (syntax_error_near(list_parsing->content));	
			}
		list_parsing = list_parsing->next;
	}
	return (0);
}

static char	is_par(char *str, char par)
{
	while (*str)
	{
		if (*str != par)
			return (0);
		str++;
	}
	return (1);
}

static char verif_par_tmp(t_parsing *list_parsing)
{
	while (list_parsing)
	{
		if (list_parsing->type == PAR_TMP)
		{
			if (is_par(list_parsing->content, '('))
				list_parsing->type = LEFT_PAR;
			else if (is_par(list_parsing->content, ')'))
				list_parsing->type = RIGHT_PAR;
			else
				return (syntax_error_near(list_parsing->content));
		}
		list_parsing = list_parsing->next;
	}
	return (0);
}

static char	is_redirect(t_parsing *token)
{
	int	type;

	if (!token)
		return (0);
	type = token->type;
	if (type == R_INPUT || type == R_OUTPUT || type == R_DINPUT
		|| type == R_DOUTPUT || type == REDIRECT_TMP)
		return (1);
	return (0);
}

static char is_cmd_arg(t_parsing *token)
{
	int	type;

	if (!token)
		return (0);
	type = token->type;
	if (type == ARG || type == CMD)
		return (1);
	return (0);
}

static char	is_and_pipe_or(t_parsing *token)
{
	int	type;

	if (!token)
		return (0);
	type = token->type;
	if (type == OR || type == AND || type == PIPE)
		return (1);
	return (0);
}

static char verif_par(t_parsing *list_parsing)
{
	int		current;
	int			nb[2];
	t_parsing	*next;

	nb[0] = 0;
	nb[1] = 0;
	while (list_parsing)
	{
		current = list_parsing->type;
		if (current == LEFT_PAR || current == RIGHT_PAR)
		{
			if (current == LEFT_PAR)
				nb[0]++;
			else
				nb[1]++;
			next = list_parsing->next;
			if (current == RIGHT_PAR
				&& !((is_redirect(next) || is_and_pipe_or(next) || !next)
				&& is_cmd_arg(list_parsing->prev)))
				return (syntax_error_near(list_parsing->content));
			if (current == LEFT_PAR
				&& !(is_cmd_arg(next)
				&& (is_and_pipe_or(list_parsing->prev) || !list_parsing->prev)))
				return (syntax_error_near(list_parsing->content));
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
			if (list_parsing->next && list_parsing->next->type == REDIRECT_TMP)
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
