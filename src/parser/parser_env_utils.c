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

char	am_i_in_dbl(char *str, char n)
{
	int		i;
	char	dbl;

	dbl = 0;
	i = 0;
	while (str[i] && i <= n)
	{
		if (str[i] == '\"' && dbl == 0)
			dbl = 1;
		else if (str[i] == '\"' && dbl)
			dbl = 0;
		i++;
	}
	if (dbl == 0)
		return (0);
	dbl = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static char	check_verif_var(char **var, char *content, int pos, int *i)
{
	while ((*var)[*i] && (*var)[*i] != '{')
		(*i)++;
	if (**var == '{' && ((*var)[*i] == '{'
		|| content[pos + 1 + *i] != '}'))
		return (syntax_error_near(*var), 2);
	return (0);
}

static char	verif_var(char **var, char *content, int pos, int *len_var)
{
	int		i;
	char	*tmp;

	i = 1;
	if (var && *var)
	{
		if (check_verif_var(var, content, pos, &i))
			return (2);
		if (**var == '{')
		{
			tmp = ft_strdup(&(*var)[1]);
			(*len_var)++;
		}
		else
		{
			(*var)[i] = '\0';
			tmp = ft_strdup(*var);
			(*len_var) = i;
		}
		free(*var);
		if (tmp == NULL)
			return (1);
		*var = tmp;
	}
	return (0);
}

char	check_var_env_txt(char **content_env[], char **var,
	int *len_var, int i)
{
	int	err;

	if (get_var_env_txt(&(*content_env[1])[i], var))
		return (1);
	if (*var)
		*len_var = ft_strlen(*var);
	err = verif_var(var, *content_env[1], i, len_var);
	if (err == 2)
		return (syntax_error_near(*content_env[1]), 2);
	else if (err)
		return (1);
	return (0);
}
