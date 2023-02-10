/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 07:04:28 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/12 11:22:13 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*cpy;

	len = ft_strlen(s);
	cpy = malloc(len + 1);
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}
