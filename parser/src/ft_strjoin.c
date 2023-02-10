/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:06:19 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/03 17:28:09 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	str = malloc(len + 1);
	if (str == NULL)
		return (str);
	i = 0;
	j = 0;
	while (i < len && s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (i < len && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
