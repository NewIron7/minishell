/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 07:31:41 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:23:26 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *) big);
	while (len && *big)
	{
		i = 0;
		while (i < len && little[i] && big[i] == little[i])
			i++;
		if (!little[i])
			return ((char *) big);
		len--;
		big++;
	}
	return (0);
}
