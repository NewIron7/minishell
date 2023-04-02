/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:56:47 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/02 10:51:24 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	am_i_in_dbl(char *str, int n)
{
	char	*next;
	char	q;

	next = str;
	while (*next)
	{
		q = check_quote(&next, str, n, "\'");
		if (q)
		{
			if (q == 1)
				return (0);
		}
		else
		{
			q = check_quote(&next, str, n, "\"");
			if (q)
			{
				if (q == 1)
					return (1);
			}
			else
				next++;
		}
	}
	return (0);
}

static char	check_verif_var(char **var, char *content, int pos, int *i)
{
	while ((*var)[*i] && is_char_var_env((*var)[*i]))
		(*i)++;
	if (**var == '{' && !is_char_var_env((*var)[*i])
			&& content[pos + 1 + *i] != '}')
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
	if (*var == NULL && (*content_env[1])[i + 1] == '?')
	{
		*var = ft_strdup("?");
		if (*var == NULL)
			return (1);
	}
	if (*var)
		*len_var = ft_strlen(*var);
	err = verif_var(var, *content_env[1], i, len_var);
	if (err == 2)
		return (2);
	else if (err)
		return (1);
	return (0);
}

char	skip_subshells(t_parsing **elem)
{
	if ((*elem)->type == LEFT_PAR)
	{
		goto_par_end(elem);
		return (1);
	}
	return (0);
}
