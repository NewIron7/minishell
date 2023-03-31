/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goto_par_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:30:38 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/31 12:11:12 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	goto_par_end(t_parsing **parsing)
{
	int	i;
	int	pars;

	i = 0;
	pars = 0;
	while ((*parsing)->type != RIGHT_PAR || pars != 1)
	{
		if ((*parsing)->type == LEFT_PAR)
			pars++;
		else if ((*parsing)->type == RIGHT_PAR)
			pars--;
		*parsing = (*parsing)->next;
		i++;
	}
	return (i);
}
