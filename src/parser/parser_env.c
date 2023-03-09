/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:17:58 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/09 19:29:03 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	get_value_var(const char *var, char **env, char **value, int code)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && var[j] && env[i][j] != '=' && env[i][j] == var[j])
			j++;
		if (var[j] == '\0' && env[i][j] == '=')
		{
			*value = ft_strdup(&env[i][j + 1]);
			if (*value == NULL)
				return (1);
			return (0);
		}
		i++;
	}
	if (ft_strcmp(var, "?") == 0)
		*value = ft_itoa(code);
	else
		*value = ft_strdup("");
	if (*value == NULL)
		return (1);
	return (0);
}

static char	insert_value_var(char **content, char *value, int len_var, int i)
{
	char	*content_tail;
	char	*content_top;
	char	*tmp;

	content_tail = ft_strdup(&(*content)[i + len_var + 1]);
	if (content_tail == NULL)
		return (free(value), 1);
	(*content)[i] = '\0';
	content_top = ft_strdup(*content);
	if (content_top == NULL)
		return (free(content_tail), free(value), 1);
	free(*content);
	tmp = ft_strjoin(content_top, value);
	free(content_top);
	free(value);
	if (tmp == NULL)
		return (free(content_tail), 1);
	*content = ft_strjoin(tmp, content_tail);
	free(content_tail);
	free(tmp);
	if (*content == NULL)
		return (1);
	return (0);
}

static char	verif_var(char **var, char *content, int pos, int *len_var)
{
	int		i;
	char	*tmp;

	i = 1;
	if (var && *var)
	{
		while ((*var)[i] && (*var)[i] != '{')
			i++;
		if (**var == '{' && ((*var)[i] == '{' || content[pos + 1 + i] != '}'))
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

static char	put_var_env_elem(char **content, char **env, int code)
{
	int		i;
	int		len_value;
	char	*var;
	char	*value;
	int		len_var;

	i = -1;
	len_var = 0;
	while ((*content)[++i])
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
	}
	return (0);
}

char	put_var_env(t_parsing **list_parsing, char **env, int code)
{
	t_parsing	*elem;
	char		err;

	elem = *list_parsing;
	while (elem)
	{
		if (elem->type == TXT || elem->type == TXT_D)
		{
			err = put_var_env_elem(&elem->content, env, code);
			if (err)
				return (err);
		}
		elem = elem->next;
	}
	return (0);
}
