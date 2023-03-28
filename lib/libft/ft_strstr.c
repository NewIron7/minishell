/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 20:00:01 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 20:00:19 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;

	if (!*little)
		return ((char *) big);
	while (*big)
	{
		i = 0;
		while (little[i] && big[i] == little[i])
			i++;
		if (!little[i])
			return ((char *) big);
		big++;
	}
	return (NULL);
}
