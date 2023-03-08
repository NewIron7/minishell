/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:20:54 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/08 14:16:50 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	*get_name_id_elem(char id)
{
	char	*txt;

	if (id == CMD)
		txt = "CMD";
	else if (id == ARG)
		txt = "ARG";
	else if (id == PIPE)
		txt = "PIPE";
	else if (id == R_INPUT)
		txt = "R_INPUT";
	else if (id == R_OUTPUT)
		txt = "R_OUTPUT";
	else if (id == R_DINPUT)
		txt = "R_DINPUT";
	else if (id == R_DOUTPUT)
		txt = "R_DOUTPUT";
	else if (id == REDIRECT_TMP)
		txt = "REDIRECT_TMP";
	else if (id == SPACE_TMP)
		txt = "SPACE_TMP";
	else if (id == TXT)
		txt = "TXT";
	else if (id == TXT_S)
		txt = "TXT_S";
	else if (id == TXT_D)
		txt = "TXT_D";
	else if (id == OR)
		txt = "OR";
	else if (id == AND)
		txt = "AND";
	else if (id == LEFT_PAR)
		txt = "LEFT_PAR";
	else if (id == RIGHT_PAR)
		txt = "RIGHT_PAR";
	else
		txt = "UNKWOWN";
	return (ft_strdup(txt));
}

void	print_list_parsing(t_parsing *list_parsing)
{
	char	*txt;
	while (list_parsing)
	{
		txt = get_name_id_elem(list_parsing->type);
		printf("[%s]-> %s\n", txt, list_parsing->content);
		free(txt);
		list_parsing = list_parsing->next;
	}
}
