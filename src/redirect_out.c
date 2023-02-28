/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:35:13 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/28 19:36:57 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_out(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		return (0);
	}
	close(fd);
	return (1);
}
