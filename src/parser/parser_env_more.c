/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:28:16 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/15 20:29:09 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	put_var_quote(char **content_env[], int code, int n)
{
	char	err;
	char	in_d;
	int		ls;

	in_d = 0;
	err = put_var_env_elem(content_env, code, n, '\'');
	if (err)
		return (err);
	while ((*content_env[1])[n] && (*content_env[1])[n] != '\'')
		n++;
	if ((*content_env[1])[n])
	{
		n++;
		ls = n;
		if (am_i_in_dbl(*content_env[1], n))
			return (put_var_quote(content_env, code, n));
		while ((*content_env[1])[n] && (*content_env[1])[n] != '\'')
			n++;
		if ((*content_env[1])[n])
			return (put_var_quote(content_env, code, n + 1));
		return (put_var_quote(content_env, code, ls));
	}
	else
		return (0);
}

char	put_var_env_elem(char **content_env[], int code, int start, char end)
{
	int		i;
	int		len_value;
	char	*var;
	char	*value;
	int		len_var;

	i = start;
	while ((*content_env[1])[i] && (*content_env[1])[i] != end)
	{
		if ((*content_env[1])[i] == '$')
		{
			len_value = check_var_env_txt(content_env, &var, &len_var, i);
			if (len_value)
				return (len_value);
			if (var)
			{
				if (get_value_var(var, content_env[0], &value, code))
					return (-1);
				if (insert_value_var(content_env[1], value, &len_var, &i))
					return (free(var), -1);
			}
		}
		i++;
	}
	return (0);
}
