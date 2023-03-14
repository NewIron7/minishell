/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:52:00 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/14 17:33:40 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	get_list_parsing(char *cmd, char *id_tab, t_parsing **list_parsing)
{
	int	size;
	int	i;

	size = ft_strlen(cmd);
	i = 0;
	*list_parsing = NULL;
	while (i < size)
	{
		if (get_elem_txt(cmd, id_tab, &i, list_parsing))
			return (1);
		if (get_space(id_tab, &i, list_parsing))
			return (1);
		if (get_elem_quoted(cmd, id_tab, &i, list_parsing))
			return (1);
		if (get_pipe(cmd, id_tab, &i, list_parsing))
			return (1);
		if (get_redirect(cmd, id_tab, &i, list_parsing))
			return (1);
		if (get_and(cmd, id_tab, &i, list_parsing))
			return (1);
		if (get_par(cmd, id_tab, &i, list_parsing))
			return (1);
	}
	return (0);
}

static void	set_cmd_arg(t_parsing *list_parsing)
{
	char	is_cmd;

	is_cmd = 1;
	while (list_parsing)
	{
		if (is_cmd && list_parsing->type == ARG
			&& (list_parsing->prev == NULL || list_parsing->prev->type == PIPE
			|| list_parsing->prev->type == ARG || list_parsing->prev->type == OR
			|| list_parsing->prev->type == AND || list_parsing->prev->type == LEFT_PAR))
		{
			list_parsing->type = CMD;
			is_cmd = 0;
		}
		else if (list_parsing->type == PIPE || list_parsing->type == OR
			|| list_parsing->type == AND || list_parsing->type == LEFT_PAR)
			is_cmd = 1;
		list_parsing = list_parsing->next;
	}
}

char	parser(char *cmd, t_parsing **list_parsing, char **env, int code)
{
	char	*id_tab;
	//char	err;

	(void)env;
	(void)code;
	if (!cmd)
		return (-1);
	cmd = ft_strtrim(cmd, " \n");
	if (!cmd)
		return (1);
	if (get_id_cmd(cmd, &id_tab))
		return (free(cmd), 1);
	if (get_list_parsing(cmd, id_tab, list_parsing))
		return (free(cmd), free(id_tab), 1);
	//err = put_var_env(list_parsing, env, code);
	//if (err)
	//	return (free(cmd), free(id_tab), err);
	if (gather_txt(*list_parsing))
		return (free(cmd), free(id_tab), 1);
	if (list_parsing_clean(*list_parsing))
		return (2);
	set_cmd_arg(*list_parsing);
	free(id_tab);
	free(cmd);
	return (0);
}
