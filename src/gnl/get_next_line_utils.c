/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:47:21 by hboissel          #+#    #+#             */
/*   Updated: 2023/01/08 16:26:56 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*gnl_free_line(char *line)
{
	free(line);
	return (NULL);
}

int	gnl_get_end_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !gnl_is_end(str[i]))
		i++;
	if (str[i])
		return (i);
	else if (!i)
		return (-2);
	else
		return (-1);
}

int	gnl_is_end(char c)
{
	if (c == 3 || c == 4 || c == 23 || c == 10)
		return (1);
	return (0);
}

char	*gnl_ft_strdup_(const char *s)
{
	int		len;
	int		i;
	char	*cpy;

	len = gnl_ft_strlen((char *)s);
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

char	*gnl_ft_strcat(char *s1, char *s2)
{
	unsigned int	length;
	unsigned int	i;
	char			*res;

	length = gnl_ft_strlen(s1) + gnl_ft_strlen(s2);
	res = malloc(length + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	gnl_free_line(s1);
	while (*s2)
		res[i++] = *(s2++);
	res[i] = 0;
	return (res);
}
