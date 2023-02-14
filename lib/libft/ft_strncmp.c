/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:10:23 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:22:53 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 == *s2 && *s1)
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return ((unsigned char) *s1 - (unsigned char) *s2);
	return (0);
}
