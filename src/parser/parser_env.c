/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:50:56 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/14 18:52:31 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	verif_var(char **var, char *content, int pos, int *len_var)
{
	int		i;
	char	*tmp;

	i = 1;
	if (var && *var)
	{
		while ((*var)[i] && (*var)[i] != '{')
			i++;
		if (**var == '{' && ((*var)[i] == '{'
			|| content[pos + 1 + i] != '}'))
			return (syntax_error_near(*var), 2);
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

static char	put_var_env_elem(char **content, char **env, int code, int start, int end)
{
	int		i;
	int		len_value;
	char	*var;
	char	*value;
	int		len_var;

	i = start;
	len_var = 0;
	while ((*content)[i] && i < end)
	{
		if ((*content)[i] == '$')
		{
			if (get_var_env_txt(&(*content)[i], &var))
				return (1);
			if (var)
				len_var = ft_strlen(var);
			len_value = verif_var(&var, *content, i, &len_var);
			if (len_value)
				return (len_value);
			if (var)
			{
				if (get_value_var(var, env, &value, code))
					return (free(var), 1);
				len_value = ft_strlen(value);
				if (insert_value_var(content, value, len_var, i))
					return (free(var), 1);
				free(var);
				i += len_value - 1;
			}
		}
		i++;
	}
	return (0);
}

char	put_var_env(t_parsing **list_parsing, char **env, int code)
{
	t_parsing	*elem;
	char		err;
	int			pos[3];
	char		*content;
	char		sep;

	elem = *list_parsing;
	while (elem)
	{
		pos[0] = 0;
		pos[1] = 0;
		if (elem->type == CMD || elem->type == ARG)
		{
			sep = '\0';
			content = elem->content;
			while (content[pos[0]])
			{
				if (sep == '\0')
				{
					if (content[pos[0]] == '\"')
					{
						err = put_var_env_elem(&elem->content, env, code, pos[1], pos[0]);
						if (err)
							return (err);
						pos[1] = pos[0] + 1;
						sep = '\"';
					}
					else if (content[pos[0]] == '\'')
						sep = '\'';
				}
				else if (content[pos[0]] == '\'' || content[pos[0]] == '\"')
				{
					if (sep == '\"' && sep == content[pos[0]])
					{
						pos[2] = pos[0];
						err = put_var_env_elem(&elem->content, env, code, pos[1], pos[2]);
						if (err)
							return (err);
						sep = '\0';
					}	
				}
				pos[0]++;
			}
			err = put_var_env_elem(&elem->content, env, code, pos[1], pos[0]);
			if (err)
				return (err);
		}
		elem = elem->next;
	}
	return (0);
}
