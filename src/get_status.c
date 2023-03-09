/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:49:40 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/09 22:54:37 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (WIFSIGNALED(status));
}
