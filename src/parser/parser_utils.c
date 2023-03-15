/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 19:01:21 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/08 13:47:55 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	identify_type_char(char c)
{
	if (c == ' ')
		return (SPACE_ID);
	if (c == '|')
		return (PIPE_C);
	if (c == '<' || c == '>')
		return (REDIRECT);
	if (c == '&')
		return (AND_ID);
	if (c == '(' || c == ')')
		return (PAR);
	return (ALPHA_NUM);
}

char	get_id_cmd(char *cmd, char **id_tab)
{
	int	size;
	int	i;

	size = ft_strlen(cmd);
	*id_tab = malloc(size + 1);
	if (!*id_tab)
		return (1);
	(*id_tab)[size] = -1;
	i = 0;
	while (i < size)
	{
		(*id_tab)[i] = identify_type_char(cmd[i]);
		i++;
	}
	return (0);
}

// char	second_quote(char *id_tab, int *i)
// {
// 	char	quote;
// 	int		j;

// 	j = *i;
// 	if (id_tab[j] == S_QUOTE)
// 		quote = S_QUOTE;
// 	else if (id_tab[j] == D_QUOTE)
// 		quote = D_QUOTE;
// 	else
// 		return (-1);
// 	j++;
// 	while (id_tab[j] != -1 && id_tab[j] != quote)
// 		j++;
// 	if (id_tab[j] != quote)
// 		return (0);
// 	return (quote);
// }

char	get_space(char *id_tab, int *i, t_parsing **list_parsing)
{
	int			size;
	t_parsing	*node;
	char		*content;

	size = 0;
	while (id_tab[*i] != -1 && id_tab[*i] == SPACE_ID)
	{
		size++;
		(*i)++;
	}
	if (size)
	{
		content = ft_strdup(" ");
		if (content == NULL)
			return (1);
		node = ft_lstnew_parsing(content, SPACE_TMP);
		if (!node)
			return (1);
		ft_lstadd_back_parsing(list_parsing, node);
	}
	return (0);
}
