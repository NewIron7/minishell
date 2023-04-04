/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 06:20:22 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/04 15:51:15 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_quotes_len(char *content, int start, int type)
{
	int	len;

	len = 0;
	while (content[start + len])
	{
		if (type == DBL && content[start + len] == '"')
			return (len);
		else if (type == SPL && content[start + len] == '\'')
			return (len);
		else if (type == DFL
			&& ((content[start + len] == '"' && ft_strchr(content + start + len + 1, '"'))
			|| (content[start + len] == '\'' && ft_strchr(content + start + len + 1, '\''))))
			return (len);
		len++;
	}
	return (len);
}

static int	get_quotes_nb(char *content)
{
	int	i;
	int	nb;
	int	type;

	if (!content[0])
		return (1);
	nb = 0;
	i = 0;
	while (content[i])
	{
		nb++;
		if (content[i] == '"' && ft_strchr(content + i + 1, '"'))
			type = DBL;
		else if (content[i] == '\'' && ft_strchr(content + i + 1, '\''))
			type = SPL;
		else
			type = DFL;
		if (type == DBL || type == SPL)
			i++;
		i += get_quotes_len(content, i, type);
		if (type == DBL || type == SPL)
			i++;
	}
	return (nb);
}

static int	fill_quotes_err(t_expand split[])
{
	int	i;

	i = 0;
	while (split[i].str)
		free(split[i++].str);
	free(split);
	return (1);
}

static int	fill_quotes_nb(t_expand split[], char *content)
{
	int	i;
	int	len;
	int	nb;
	int	type;

	if (!content[0])
	{
		split[0].str = ft_strdup("");
		split[0].type = DFL;
		if (!split[0].str)
			return (0);
		else
			return (1);
	}
	nb = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '"' && ft_strchr(content + i + 1, '"'))
			type = DBL;
		else if (content[i] == '\'' && ft_strchr(content + i + 1, '\''))
			type = SPL;
		else
			type = DFL;
		if (type == DBL || type == SPL)
			i++;
		len = get_quotes_len(content, i, type);
		split[nb].str = ft_substr(content, i, len);
		split[nb].type = type;
		if (type == DBL || type == SPL)
			i++;
		if (!split[nb].str)
			return (fill_quotes_err(split));
		nb++;
		i += len;
	}
	return (1);
}

int	split_quotes(t_expand *split[], char *content)
{
	int	nb;

	nb = get_quotes_nb(content);
	*split = malloc(sizeof(t_expand) * (nb + 1));
	if (!*split)
		return (0);
	if (!fill_quotes_nb(*split, content))
		return (0);
	(*split)[nb].str = NULL;
	return (1);
}
