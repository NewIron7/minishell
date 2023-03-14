/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:49:13 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/14 18:49:58 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	get_par(char *cmd, char *id_tab, int *i, t_parsing **list_parsing)
{
	int			size;
	char		*elem;
	t_parsing	*node;

	if (id_tab[*i] != PAR)
		return (0);
	size = 1;
	elem = malloc(size + 1);
	if (!elem)
		return (1);
	elem[size] = 0;
	elem[0] = cmd[*i];
	(*i)++;
	node = ft_lstnew_parsing(elem, PAR_TMP);
	if (!node)
		return (free(elem), 1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}

char	get_and(char *cmd, char *id_tab, int *i, t_parsing **list_parsing)
{
	int			size;
	char		*elem;
	int			j;
	t_parsing	*node;

	size = get_size_elem_type(id_tab, i, AND_ID, AND_ID);
	if (!size)
		return (0);
	*i -= size;
	elem = malloc(size + 1);
	if (!elem)
		return (1);
	elem[size] = 0;
	j = 0;
	while (id_tab[*i] != -1 && id_tab[*i] == AND_ID)
	{
		elem[j] = cmd[*i];
		(*i)++;
		j++;
	}
	node = ft_lstnew_parsing(elem, AND);
	if (!node)
		return (free(elem), 1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}
