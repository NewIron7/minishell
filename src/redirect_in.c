/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:31:14 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/28 19:37:10 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell");
		return (0);
	}
	close(fd);
	return (1);
}
