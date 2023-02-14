/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <ddelhalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 19:46:34 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/01/21 23:09:12 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*memdst;
	const unsigned char	*memsrc;

	if (!dest && !src)
		return (NULL);
	memsrc = src;
	memdst = dest;
	if (src > dest)
	{
		while (n--)
			*(memdst++) = *(memsrc++);
	}
	else if (src < dest)
	{
		while (n--)
			memdst[n] = memsrc[n];
	}
	return (dest);
}
