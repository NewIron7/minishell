/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:32:10 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:23:02 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*mem;

	mem = s;
	while (n--)
	{
		if (*mem == (unsigned char) c)
			return ((void *) mem);
		mem++;
	}
	return (0);
}
