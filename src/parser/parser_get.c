/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:57:28 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/23 19:33:32 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

int	get_size_elem_type(char *id_tab, int *i, char id_1, char id_2)
{
	int	size;

	size = 0;
	while (id_tab[*i] != -1
		&& (id_tab[*i] == id_1 || id_tab[*i] == id_2))
	{
		size++;
		(*i)++;
	}
	return (size);
}

char	get_elem_txt(char *cmd, char *id_tab, int *i,
		t_parsing **list_parsing)
{
	int			size;
	char		*elem;
	int			j;
	t_parsing	*node;

	size = get_size_elem_type(id_tab, i, ALPHA_NUM, ALPHA_NUM);
	if (!size)
		return (0);
	*i -= size;
	elem = malloc(size + 1);
	if (!elem)
		return (1);
	elem[size] = 0;
	j = 0;
	while (j < size)
	{
		elem[j] = cmd[*i];
		(*i)++;
		j++;
	}
	node = ft_lstnew_parsing(elem, TXT);
	if (!node)
		return (free(elem), 1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}

char	get_pipe(char *cmd, char *id_tab, int *i, t_parsing **list_parsing)
{
	int			size;
	char		*elem;
	int			j;
	t_parsing	*node;

	size = get_size_elem_type(id_tab, i, PIPE_C, PIPE_C);
	if (!size)
		return (0);
	*i -= size;
	elem = malloc(size + 1);
	if (!elem)
		return (1);
	elem[size] = 0;
	j = 0;
	while (id_tab[*i] != -1 && id_tab[*i] == PIPE_C)
	{
		elem[j] = cmd[*i];
		(*i)++;
		j++;
	}
	node = ft_lstnew_parsing(elem, PIPE);
	if (!node)
		return (free(elem), 1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}

char	get_redirect(char *cmd, char *id_tab, int *i,
		t_parsing **list_parsing)
{
	int			size;
	char		*elem;
	int			j;
	t_parsing	*node;

	size = get_size_elem_type(id_tab, i, REDIRECT, REDIRECT);
	if (!size)
		return (0);
	*i -= size;
	elem = malloc(size + 1);
	if (!elem)
		return (1);
	elem[size] = 0;
	j = 0;
	while (id_tab[*i] != -1 && id_tab[*i] == REDIRECT)
	{
		elem[j] = cmd[*i];
		(*i)++;
		j++;
	}
	node = ft_lstnew_parsing(elem, REDIRECT_TMP);
	if (!node)
		return (free(elem), 1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}
