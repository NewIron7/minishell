/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_utils_more.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:38:04 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/14 19:39:12 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	get_value_var(char *var, char **env, char **value, int code)
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
				return (free(var), 1);
			return (free(var), 0);
		}
		i++;
	}
	if (ft_strcmp(var, "?") == 0)
		*value = ft_itoa(code);
	else
		*value = ft_strdup("");
	if (*value == NULL)
		return (free(var), 1);
	return (free(var), 0);
}

int	insert_value_var(char **content, char *value, int *len_var, int *i)
{
	char	*content_tail;
	char	*content_top;
	char	*tmp;

	content_tail = ft_strdup(&(*content)[*i + *len_var + 1]);
	if (content_tail == NULL)
		return (free(value), 1);
	(*content)[*i] = '\0';
	content_top = ft_strdup(*content);
	if (content_top == NULL)
		return (free(content_tail), free(value), 1);
	free(*content);
	tmp = ft_strjoin(content_top, value);
	free(content_top);
	*i += ft_strlen(value) - 1;
	free(value);
	if (tmp == NULL)
		return (free(content_tail), -1);
	*content = ft_strjoin(tmp, content_tail);
	free(content_tail);
	*len_var = ft_strlen(tmp);
	free(tmp);
	if (*content == NULL)
		return (1);
	return (0);
}

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

char	move_right_part(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (0);
}
