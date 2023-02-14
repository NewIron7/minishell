/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:57:15 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:19:56 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*memsrc;
	unsigned char		*memdst;

	if (!dest && !src)
		return (NULL);
	memsrc = src;
	memdst = dest;
	while (n--)
		*(memdst++) = *(memsrc++);
	return (dest);
}
