/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 04:48:55 by hboissel          #+#    #+#             */
/*   Updated: 2023/01/08 17:16:43 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	gnl_ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*gnl_get_line(char *buf, int end)
{
	char	*line;
	int		i;

	if (end < 0)
	{
		line = gnl_ft_strdup_(buf);
		buf[0] = 0;
		return (line);
	}
	line = malloc(end + 2);
	if (!line)
		return (NULL);
	i = -1;
	while (++i <= end)
		line[i] = buf[i];
	line[i] = 0;
	i = 0;
	while (buf[++end])
		buf[i++] = buf[end];
	buf[i] = 0;
	return (line);
}

static char	*check_prev(t_tool *vars, char *buf)
{
	char	*tmp;

	while (vars->end == -1 && buf[0] != 0)
	{
		vars->end = gnl_get_end_line(buf);
		tmp = gnl_get_line(buf, vars->end);
		if (!tmp)
			return (gnl_free_line(vars->line));
		vars->line = gnl_ft_strcat(vars->line, tmp);
		free(tmp);
		if (!vars->line)
			return (NULL);
	}
	return ("");
}

static char	*next_line(int fd)
{
	static char	buf[(BUFFER_SIZE > 0) * BUFFER_SIZE + 1];
	int			ctrl;
	char		*tmp;
	t_tool		vars;

	vars.line = gnl_ft_strdup_("");
	vars.end = -1;
	if (!check_prev(&vars, buf))
		return (gnl_free_line(vars.line));
	while (vars.end == -1)
	{
		ctrl = read(fd, buf, (BUFFER_SIZE > 0) * BUFFER_SIZE);
		if (ctrl == -1 || (ctrl == 0 && !*vars.line))
			return (gnl_free_line(vars.line));
		buf[ctrl] = 0;
		vars.end = gnl_get_end_line(buf);
		tmp = gnl_get_line(buf, vars.end);
		if (!tmp)
			return (gnl_free_line(vars.line));
		vars.line = gnl_ft_strcat(vars.line, tmp);
		free(tmp);
		if (!vars.line)
			return (NULL);
	}
	return (vars.line);
}

char	*get_next_line(int fd)
{
	if (BUFFER_SIZE > 0)
		return (next_line(fd));
	return (NULL);
}
