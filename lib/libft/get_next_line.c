/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:27:36 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/30 15:47:07 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	gnl_linelen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}

static char	*gnl_strnjoin(char *s1, char *s2, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (s2[len])
		i = 1;
	if (!s1)
		return (ft_substr(s2, 0, len + i));
	new = malloc((gnl_linelen(s1) + len + 1 + i) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (*s1)
		new[i++] = *s1++;
	while (*s2 && *s2 != '\n')
		new[i++] = *s2++;
	if (*s2 == '\n')
		new[i++] = *s2;
	new[i] = 0;
	return (new);
}

static ssize_t	gnl_load_buffer(int fd, char *buffer, size_t *start)
{
	ssize_t	ret;

	*start = 0;
	ret = read(fd, buffer, FT_BUFFER_SIZE);
	if (ret >= 0)
		buffer[ret] = 0;
	return (ret);
}

static ssize_t	gnl_read_line(int fd, char **line, size_t *start, char *buffer)
{
	size_t	len;
	char	*new;

	len = gnl_linelen(buffer + *start);
	new = gnl_strnjoin(*line, buffer + *start, len);
	if (!new)
		return (-1);
	free(*line);
	*line = new;
	*start += len;
	if (buffer[*start])
	{
		(*start)++;
		return (0);
	}
	return (gnl_load_buffer(fd, buffer, start));
}

char	*get_next_line(int fd)
{
	static char		buffer[FT_BUFFER_SIZE + 1] = {0};
	static size_t	start = 0;
	ssize_t			ret;
	char			*line;

	line = NULL;
	ret = 1;
	if (!buffer[start])
	{
		ret = gnl_load_buffer(fd, buffer, &start);
		if (ret <= 0)
		{
			if (ret)
				free(line);
			return (NULL);
		}
	}
	while (ret > 0)
		ret = gnl_read_line(fd, &line, &start, buffer);
	if (ret < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
