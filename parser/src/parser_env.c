/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:17:58 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/10 18:46:06 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static char	is_char_var_env(char c)
{
	if (c == ' ' || c == '$' || c == '-')
		return (0);
	else if (c == '/')
		return (0);
	return (1);
}

char	get_var_env_txt(const char *txt, char **var)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	*var = NULL;
	while (txt[i] && txt[i] != '$')
		i++;
	if (txt[i] == '\0')
		return (0);
	size = 0;
	i++;
	while (txt[i] && is_char_var_env(txt[i]))
	{
		i++;
		size++;
	}
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

char	get_value_var(const char *var, char **env, char **value)
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
	*value = ft_strdup("");
	if (*value == NULL)
		return (1);
	return (0);
}

char	insert_value_var(char **content, char *value, int len_var, int i)
{
	char	*content_tail;
	char	*content_top;
	char	*tmp;

	content_tail = ft_strdup(&(*content)[i + len_var + 1]);
	if (content_tail == NULL)
		return (1);
	(*content)[i] = '\0';
	content_top = ft_strdup(*content);
	if (content_top == NULL)
		return (free(content_tail), 1);
	free(*content);
	tmp = ft_strjoin(content_top, value);
	free(content_top);
	free(value);
	if (tmp == NULL)
		return (free(content_tail), 1);
	*content = ft_strjoin(tmp, content_tail);
	free(content_tail);
	if (*content == NULL)
		return (1);
	return (0);
}

char	put_var_env_elem(char **content, char **env)
{
	int		i;
	int		len_value;
	char	*var;
	char	*value;

	i = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '$')
		{
			if (get_var_env_txt(&(*content)[i], &var))
				return (1);
			if (var)
			{
				if (get_value_var(var, env, &value))
					return (1);
				len_value = ft_strlen(value);
				if (insert_value_var(content, value, ft_strlen(var), i))
					return (1);
				i += len_value - 1;
			}
		}
		i++;
	}
	return (0);
}

char	put_var_env(t_parsing **list_parsing, char **env)
{
	t_parsing	*elem;

	elem = *list_parsing;
	while (elem)
	{
		if (elem->type == TXT || elem->type == TXT_D)
		{
			if (put_var_env_elem(&elem->content, env))
				return (1);
		}
		elem = elem->next;
	}
	return (0);
}
