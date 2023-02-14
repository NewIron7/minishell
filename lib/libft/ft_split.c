/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 04:56:16 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:26:05 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countsplit(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s && *s == c)
		s++;
	if (*s)
	{
		count++;
		s = ft_strchr(s, c);
	}
	while (s && *s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			count++;
			s = ft_strchr(s, c);
		}
	}
	return (count);
}

static void	*ft_freesplit(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	*next;
	char	**tab;
	size_t	i;

	tab = ft_calloc(ft_countsplit(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (s && *s)
	{
		while (*s && *s == c)
			s++;
		next = ft_strchr(s, c);
		if (*s)
		{
			if (next)
				tab[i] = ft_substr(s, 0, next - s);
			else
				tab[i] = ft_strdup(s);
			if (!tab[i++])
				return (ft_freesplit(tab));
		}
		s = next;
	}
	return (tab);
}
