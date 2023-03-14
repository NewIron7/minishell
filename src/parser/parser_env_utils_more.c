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

char	get_value_var(const char *var, char **env, char **value, int code)
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

char	insert_value_var(char **content, char *value, int len_var, int i)
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
