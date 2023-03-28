/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:36:19 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/28 16:37:25 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	check_ctrl_d(char *line, char *end)
{
	if (line == NULL)
	{
		ft_printf_fd(2, "minishell: warning: here-document at line 1 ");
		ft_printf_fd(2, "delimited by end-of-file (wanted `%s')\n", end);
		return (1);
	}
	return (0);
}
