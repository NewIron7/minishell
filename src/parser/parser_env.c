/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:50:56 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/15 15:34:26 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	check_next_quote(char *str, int *i, char *q, char ls)
{
	while (str[*i] && str[*i] != *q)
		(*i)++;
	if (str[*i] == '\0')
	{
		*i = ls;
		*q = 0;
	}
	else
		return (1);
	return (0);
}

static char	do_move_right(char *str, char *q, int *i, int ls)
{
	*q = 0;
	move_right_part(str + ls);
	move_right_part(str + *i - 1);
	*i -= 2;
	return (0);
}

static char	check_current_quote(char *str, char *q, int *i, int *ls)
{
	if (*q == 0)
	{
		*ls = *i;
		*q = str[*i];
	}
	else if (*q == str[*i])
		do_move_right(str, q, i, *ls);
	else
	{
		if (check_next_quote(str, i, q, *ls))
			return (1);
	}
	return (0);
}

static char	rm_quotes(char *str)
{
	int		i;
	int		ls;
	char	q;

	ls = 0;
	i = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (check_current_quote(str, &q, &i, &ls))
				continue ;
		}
		i++;
	}
	return (0);
}

char	put_var_env(t_parsing **list_parsing, char **env, int code)
{
	t_parsing	*elem;
	int			err;
	char		**content_env[2];

	content_env[0] = env;
	elem = *list_parsing;
	while (elem && elem->type != AND && elem->type != OR
		&& elem->type != LEFT_PAR)
	{
		if (elem->type == CMD || elem->type == ARG)
		{
			content_env[1] = &elem->content;
			err = put_var_quote(content_env, code, 0);
			if (err)
				return (err);
			rm_quotes(elem->content);
		}
		elem = elem->next;
	}
	return (0);
}
