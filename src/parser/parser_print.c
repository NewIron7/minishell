/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:20:54 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/20 19:21:17 by hboissel         ###   ########.fr       */
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
		txt = "R_outPUT";
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
	else
		txt = "UNKWOWN";
	return (ft_strdup(txt));
}

void	print_list_parsing(t_parsing *list_parsing)
{
	while (list_parsing)
	{
		printf("[%s]-> %s\n",
			get_name_id_elem(list_parsing->type), list_parsing->content);
		list_parsing = list_parsing->next;
	}
}
