/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:02:04 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/29 10:02:27 by ddelhalt         ###   ########.fr       */
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

char	rm_quotes(char *str)
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
