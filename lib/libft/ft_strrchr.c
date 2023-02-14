/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:59:56 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:22:42 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	if ((char) c == 0)
		return ((char *) s + ft_strlen(s));
	last = 0;
	while (*s)
	{
		if (*s == (char) c)
			last = s;
		s++;
	}
	return ((char *) last);
}
