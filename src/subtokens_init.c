/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtokens_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:04:58 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/08 13:34:38 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_subtokens	subtokens_init(t_parsing *tokens, int start, int sep, int end)
{
	t_subtokens	subtokens;

	subtokens.tokens = tokens;
	subtokens.start = start;
	subtokens.sep = sep;
	subtokens.end = end;
	return (subtokens);
}
