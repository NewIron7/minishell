/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:50:56 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/02 11:01:20 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	expand_elems(t_parsing *elem, t_parsing **next)
{
	if (!expand_elem(elem, &space_split))
		return (0);
	*next = elem->next;
	if (!expand_elem(elem, &expand_wildcard))
		return (0);
	return (1);
}

static char	call_to_expand_elems(t_parsing *elem, t_parsing **next)
{
	if (!elem->prev || !is_redirect(elem->prev))
	{
		if (!expand_elems(elem, next))
			return (1);
	}
	else
	{
		rm_quotes(elem->content);
		*next = elem->next;
	}
	return (0);
}

char	put_var_env(t_parsing **list_parsing, char **env, int code)
{
	t_parsing	*elem;
	t_parsing	*next;
	int			err;
	char		**content_env[2];

	content_env[0] = env;
	elem = *list_parsing;
	while (elem && elem->type != AND && elem->type != OR
		&& elem->type != RIGHT_PAR && elem->type != PIPE)
	{
		if (!skip_subshells(&elem)
			&& (elem->type == CMD || elem->type == ARG))
		{
			content_env[1] = &elem->content;
			err = put_var_quote(content_env, code, 0);
			if (err)
				return (err);
			if (call_to_expand_elems(elem, &next))
				return (EXIT_FAILURE);
		}
		else
			next = elem->next;
		elem = next;
	}
	return (0);
}
