/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:26:57 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/08 15:07:01 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

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
	}
	return (0);
}

static char    verif_and(t_parsing *list_parsing)
{
	while (list_parsing)
	{
		if (list_parsing->type == AND)
		{
			if (is_unvalid_next_token(list_parsing) || ft_strcmp_parsing(list_parsing->content, "&&"))
			{
				printf("minishell: syntax error near unexpected token '%s'\n", list_parsing->content);
				return (1);
			}
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
            {
                printf("minishell: syntax error near unexpected token '%s'\n", list_parsing->content);
                return (1);
            }
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

static char verif_par(t_parsing *list_parsing)
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
			{
				printf("minishell: syntax error near unexpected token '%s'\n", list_parsing->content);
				return (1);
			}
		}
		list_parsing = list_parsing->next;
	}
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
			{
				printf("minishell: syntax error near unexpected token '%s'\n", content);
				return (1);
			}
			if (!ft_strcmp_parsing(content, "<"))
				list_parsing->type = R_INPUT;
			else if (!ft_strcmp_parsing(content, ">"))
				list_parsing->type = R_OUTPUT;
			else if (!ft_strcmp_parsing(content, "<<"))
				list_parsing->type = R_DINPUT;
			else if (!ft_strcmp_parsing(content, ">>"))
				list_parsing->type = R_DOUTPUT;
			else
			{
				printf("minishell: syntax error near unexpected token '%s'\n", content);
				return (1);
			}
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
	if (verif_par(list_parsing))
		return (1);
	return (0);
}
