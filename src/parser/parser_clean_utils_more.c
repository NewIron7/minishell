/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_utils_more.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:13:38 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/14 19:32:26 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	is_par(char *str, char par)
{
	while (*str)
	{
		if (*str != par)
			return (0);
		str++;
	}
	return (1);
}

char	verif_par_tmp(t_parsing *list_parsing)
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

char	is_redirect(t_parsing *token)
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

char	is_cmd_arg(t_parsing *token)
{
	int	type;

	if (!token)
		return (0);
	type = token->type;
	if (type == ARG || type == CMD)
		return (1);
	return (0);
}

char	is_and_pipe_or(t_parsing *token)
{
	int	type;

	if (!token)
		return (0);
	type = token->type;
	if (type == OR || type == AND || type == PIPE)
		return (1);
	return (0);
}
