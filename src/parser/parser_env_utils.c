/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:56:47 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/14 18:02:37 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	is_char_var_env(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '{')
		return (1);
	return (0);
}

char	get_var_env_txt(const char *txt, char **var)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	*var = NULL;
	size = 0;
	while (txt[++i] && is_char_var_env(txt[i]))
		size++;
	if (size == 0)
		return (0);
	*var = malloc(size + 1);
	if (*var == NULL)
		return (1);
	(*var)[size] = 0;
	i -= size;
	j = 0;
	while (j < size)
	{
		(*var)[j] = txt[i];
		i++;
		j++;
	}
	return (0);
}
