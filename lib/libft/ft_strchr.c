/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 03:03:39 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:22:17 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if ((char) c == 0)
		return ((char *) s + ft_strlen(s));
	while (*s)
	{
		if (*s == (char) c)
			return ((char *) s);
		s++;
	}
	return (0);
}
