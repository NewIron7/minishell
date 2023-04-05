/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:53:26 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 09:53:59 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_quote_type(char *content, int start)
{
	if (content[start] == '"' && ft_strchr(content + start + 1, '"'))
		return (DBL);
	else if (content[start] == '\'' && ft_strchr(content + start + 1, '\''))
		return (SPL);
	else
		return (DFL);
}

int	get_quotes_len(char *content, int start, int type)
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
			&& ((content[start + len] == '"'
					&& ft_strchr(content + start + len + 1, '"'))
				|| (content[start + len] == '\''
					&& ft_strchr(content + start + len + 1, '\''))))
			return (len);
		len++;
	}
	return (len);
}
