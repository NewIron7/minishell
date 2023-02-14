/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 03:57:47 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:25:21 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*new;
	size_t	i;

	len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	new[i] = 0;
	return (new);
}
