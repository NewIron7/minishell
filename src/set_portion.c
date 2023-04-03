/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_portion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 03:45:27 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/03 03:46:35 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_portion	set_portion(t_parsing *start, t_parsing *end)
{
	t_portion	chunck;

	chunck.start = start;
	chunck.end = end;
	return (chunck);
}
