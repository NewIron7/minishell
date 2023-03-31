/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 12:04:39 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/31 12:11:48 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection(t_parsing *tokens, int start, int end)
{
	int	i;
	int	redirs;

	i = -1;
	redirs = 0;
	while ((end != -1 && ++i < end - start) || (end == -1 && tokens))
	{
		if (tokens->type == LEFT_PAR)
			goto_par_end(&tokens);
		else if (tokens->type == R_INPUT || tokens->type == R_OUTPUT
			|| tokens->type == R_DINPUT || tokens->type == R_DOUTPUT)
			redirs++;
		tokens = tokens->next;
	}
	return (redirs);
}
