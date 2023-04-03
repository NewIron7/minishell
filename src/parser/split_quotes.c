/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 06:20:22 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/03 07:44:15 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_quotes_nb(char *content)
{
	int		nb;
	int		is_dfl;
	char	*next;

	is_dfl = 1;
	nb = 0;
	if (*content != '"' && *content != '\'')
		nb = 1;
	while (*content)
	{
		next = NULL;
		if (*content == '"')
			next = ft_strchr(content + 1, '"');
		else if (*content == '\'')
			next = ft_strchr(content + 1, '\'');
		if (!next && !is_dfl)
		{
			nb++;
			is_dfl = 1;
		}
		if (next)
		{
			nb++;
			is_dfl = 0;
			content = next;
		}
		content++;
	}
}

static int	get_quote_len(char *content, int start, int type)
{
	int	len;

	if (content[i] == '"' && ft_strchr(content + i + 1, '"'))
		type = DBL;
	else if (content[i] == '\'' && ft_strchr(content + i + 1, '\''))
		type = SPL;
	else if (content[i])
		type = DFL;
	len = 0;
	while (content[start + len])
	{
		if (type == DBL && content[start + len] == '"')
			return (len);
		else if (type == SPL && content[start + len] == '\'')
			return (len);
		else if (type == DFL
			&& ((content[start + len] == '"' || ft_strchr(content + start + len + 1, '"'))
			|| (content[start + len] == '\'' || ft_strchr(content + start + len + 1, '\'')))
			return (len);
		len++;
	}
	return (len);
}

static int	fill_quotes_nb(t_expand split[], char *content)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	while (content[i])
	{

int	split_quotes(t_expand *split[], char *content)
{
	int	nb;

	len = get_quotes_nb(content);
	*split = malloc(sizeof(t_expand) * (len + 1));
	if (!*split)
		return (0);
	if (!fill_quotes_nb(*split, content))
		return (0);
	(*split)[len].str = NULL;
	return (1);
