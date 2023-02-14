/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 07:26:30 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:26:32 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*new;

	len = ft_strlen(s);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	new[len] = 0;
	while (len--)
		new[len] = (*f)(len, s[len]);
	return (new);
}
