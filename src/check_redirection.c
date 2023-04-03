/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:04:39 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/03 01:08:21 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(t_portion chunck)
{
	int	redirs;

	redirs = 0;
	while (chunck.start != chunck.end)
	{
		if (chunck.start->type == LEFT_PAR)
			chunck.start = goto_par_end(chunck.start);
		else if (chunck.start->type == R_INPUT || chunck.start->type == R_OUTPUT
			|| chunck.start->type == R_DINPUT || chunck.start->type == R_DOUTPUT)
			redirs++;
		chunck.start = chunck.start->next;
	}
	return (redirs);
}
