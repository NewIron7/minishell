/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 07:09:01 by hboissel          #+#    #+#             */
/*   Updated: 2022/11/14 08:34:55 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	ft_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*ft_empty(void)
{
	char	*res;

	res = malloc(1);
	if (!res)
		return (res);
	res[0] = 0;
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		r;
	int		j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && ft_in_set(s1[i], (char *)set))
		i++;
	r = ft_strlen(s1) - 1;
	while (r >= 0 && ft_in_set(s1[r], (char *)set))
		r--;
	if (i > r)
		return (ft_empty());
	trim = malloc(r - i + 2);
	if (!trim)
		return (NULL);
	j = 0;
	while (i <= r)
		trim[j++] = s1[i++];
	trim[j] = 0;
	return (trim);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%s\n", ft_strtrim(argv[1], argv[2]));
	return (0);
}*/
