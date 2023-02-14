/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 04:31:00 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:25:42 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, char const *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			len;

	while (*s1 && ft_isset(*s1, set))
		s1++;
	len = ft_strlen(s1);
	while (len && ft_isset(s1[len - 1], set))
		len--;
	return (ft_substr(s1, 0, len));
}
