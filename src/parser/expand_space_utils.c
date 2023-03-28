/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_space_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:15:53 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/28 16:17:32 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_split(char *str)
{
	int		count;
	char	*next;

	count = 0;
	while (*str)
	{
		next = NULL;
		if (*str == '"')
			next = ft_strchr(str + 1, '"');
		else if (*str == '\'')
			next = ft_strchr(str + 1, '\'');
		else if (ft_isspace(*str))
		{
			while (ft_isspace(*str + 1))
				str++;
			if (*str + 1)
				count++;
		}
		if (next)
			str = next;
		str++;
	}
	return (count);
}

static void	free_split(char ***split)
{
	char	**cpy;

	cpy = *split;
	while (*cpy)
		free(*cpy++);
	free(*split);
	*split = NULL;
}

char	*check_cpy(char *cpy)
{
	char	*next;

	next = NULL;
	if (*cpy == '"')
		next = ft_strchr(cpy + 1, '"');
	else if (*cpy == '\'')
		next = ft_strchr(cpy + 1, '\'');
	return (next);
}

int	fill_split(char **str, int i, char ***split)
{
	int		strlen;
	char	*next;
	char	*cpy;

	strlen = 0;
	cpy = *str;
	while (!ft_isspace(*cpy))
	{
		next = check_cpy(cpy);
		if (next)
		{
			strlen += next - cpy;
			cpy = next;
		}
		strlen++;
		cpy++;
	}
	(*split)[i] = ft_substr((*str), 0, strlen);
	if (!(*split)[i])
		return (free_split(split), 0);
	(*str) += strlen;
	return (1);
}
