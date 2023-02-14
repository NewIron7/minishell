/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:44:19 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:23:13 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*mem1;
	const unsigned char	*mem2;

	mem1 = s1;
	mem2 = s2;
	while (n && *mem1 == *mem2)
	{
		n--;
		mem1++;
		mem2++;
	}
	if (n)
		return (*mem1 - *mem2);
	return (0);
}
