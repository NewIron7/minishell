/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 06:20:22 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 14:57:13 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		type = get_quote_type(content, i);
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

static int	fill_quote_split(t_expand *quote, char *content, int start)
{
	int	len;
	int	i;

	i = 0;
	quote->type = get_quote_type(content, start);
	if (quote->type == DBL || quote->type == SPL)
		i++;
	len = get_quotes_len(content, start + i, quote->type);
	quote->str = ft_substr(content, start + i, len);
	if (quote->type == DBL || quote->type == SPL)
		i++;
	return (i + len);
}

static int	fill_quotes_split(t_expand split[], char *content)
{
	int	i;
	int	nb;

	if (!content[0])
	{
		split[0].type = DFL;
		split[0].str = ft_strdup("");
		nb = 1;
	}
	nb = 0;
	i = 0;
	while (content[i])
	{
		i += fill_quote_split(&split[nb], content, i);
		if (!split[nb].str)
			break ;
		nb++;
	}
	if (!split[nb - 1].str)
		return (fill_quotes_err(split));
	return (1);
}

int	split_quotes(t_expand *split[], char *content)
{
	int	nb;

	nb = get_quotes_nb(content);
	*split = malloc(sizeof(t_expand) * (nb + 1));
	if (!*split)
		return (0);
	if (!fill_quotes_split(*split, content))
		return (0);
	(*split)[nb].str = NULL;
	return (1);
}
