/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:14:34 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/12/15 15:22:11 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_basename(char *cmd)
{
	char	*base;

	base = cmd;
	while (*cmd)
	{
		if (*cmd == '\\')
			cmd++;
		else if (*cmd == '/')
			base = cmd + 1;
		cmd++;
	}
	return (base);
}
