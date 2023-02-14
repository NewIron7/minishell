/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 03:11:02 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:25:04 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a <= b)
		return (a);
	return (b);
}

static size_t	max_len(unsigned int start, size_t len)
{
	if (start >= len)
		return (0);
	return (len - start);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	len = min(len, max_len(start, ft_strlen(s)));
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	s += start;
	new[len] = 0;
	while (len--)
		new[len] = s[len];
	return (new);
}
