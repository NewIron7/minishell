/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:38:32 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/20 19:56:26 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	get_size_quoted(char *id_tab, int *i, char quote)
{
	int	size;

	size = 0;
	(*i)++;
	while (id_tab[*i] != -1 && id_tab[*i] != quote)
	{
		size++;
		(*i)++;
	}
	(*i)++;
	return (size);
}

char	*get_in_quotes(char *cmd, int *i, int size)
{
	char	*elem;
	int		j;

	elem = malloc(size + 1);
	if (!elem)
		return (NULL);
	elem[size] = 0;
	j = 0;
	while (j < size)
	{
		elem[j] = cmd[*i];
		(*i)++;
		j++;
	}
	(*i)++;
	return (elem);
}

static char	add_quoted_node(char *elem, char quote, t_parsing **list_parsing)
{
	t_parsing	*node;

	if (quote == S_QUOTE)
		node = ft_lstnew_parsing(elem, TXT_S);
	else
		node = ft_lstnew_parsing(elem, TXT_D);
	if (!node)
		return (1);
	ft_lstadd_back_parsing(list_parsing, node);
	return (0);
}

char	get_elem_quoted(char *cmd, char *id_tab, int *i,
		t_parsing **list_parsing)
{
	int			size;
	char		*elem;
	char		quote;

	quote = second_quote(id_tab, i);
	if (!quote)
	{
		id_tab[*i] = ALPHA_NUM;
		return (0);
	}
	if (quote == -1)
		return (0);
	size = get_size_quoted(id_tab, i, quote);
	if (!size)
		return (0);
	*i -= size + 1;
	elem = get_in_quotes(cmd, i, size);
	if (elem == NULL)
		return (1);
	if (add_quoted_node(elem, quote, list_parsing))
		return (1);
	return (0);
}
