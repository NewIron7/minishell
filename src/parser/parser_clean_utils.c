/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:54:28 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/28 15:50:15 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	syntax_error_near(char *str)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n", str);
	return (2);
}

char	ft_strcmp_parsing(char *str1, char *str2)
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

char	unvalid_token(t_parsing *tokens)
{
	char	next;

	if (tokens && tokens->next)
	{
		if (tokens->prev == NULL)
			return (1);
		next = tokens->next->type;
		if (next == AND || next == OR || next == PIPE)
			return (1);
		return (0);
	}
	return (1);
}

char	verif_and(t_parsing *list_parsing)
{
	while (list_parsing)
	{
		if (list_parsing->type == AND)
		{
			if (unvalid_token(list_parsing)
				|| ft_strcmp_parsing(list_parsing->content, "&&"))
				return (syntax_error_near(list_parsing->content));
		}
		list_parsing = list_parsing->next;
	}
	return (0);
}

char	verif_pipe(t_parsing *list_parsing)
{
	char	*content;

	while (list_parsing)
	{
		if (list_parsing->type == PIPE)
		{
			content = list_parsing->content;
			if (!ft_strcmp_parsing(content, "||"))
				list_parsing->type = OR;
			if (unvalid_token(list_parsing) || (ft_strcmp_parsing(content, "|")
					&& list_parsing->type != OR))
				return (syntax_error_near(content));
		}
		list_parsing = list_parsing->next;
	}
	return (0);
}
