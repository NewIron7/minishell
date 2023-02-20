/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:26:57 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/20 18:50:21 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	ft_strcmp(char *str1, char *str2)
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

char	verif_pipe(t_parsing *list_parsing)
{
	while (list_parsing)
	{
		if (list_parsing->type == PIPE && ft_strcmp(list_parsing->content, "|"))
		{
			printf("minishell: parse error near '%s'\n", list_parsing->content);
			return (1);
		}
		list_parsing = list_parsing->next;
	}
	return (0);
}

char	verif_redirect(t_parsing *list_parsing)
{
	char	*content;

	while (list_parsing)
	{
		if (list_parsing->type == REDIRECT_TMP)
		{
			content = list_parsing->content;
			if (!ft_strcmp(content, "<"))
				list_parsing->type = R_INPUT;
			else if (!ft_strcmp(content, ">"))
				list_parsing->type = R_OUTPUT;
			else if (!ft_strcmp(content, "<<"))
				list_parsing->type = R_DINPUT;
			else if (!ft_strcmp(content, ">>"))
				list_parsing->type = R_DOUTPUT;
			else
			{
				printf("minishell: parse error near '%s'\n", content);
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
	return (0);
}
