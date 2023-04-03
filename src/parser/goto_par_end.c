/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_par_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:30:38 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/03 02:59:25 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parsing	*goto_par_end(t_parsing *parsing)
{
	int	pars;

	pars = 0;
	while (parsing->type != RIGHT_PAR || pars != 1)
	{
		if (parsing->type == LEFT_PAR)
			pars++;
		else if (parsing->type == RIGHT_PAR)
			pars--;
		parsing = parsing->next;
	}
	return (parsing);
}
