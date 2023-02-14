/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:14:15 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/12/01 09:37:39 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_read_line_err(t_list **list, int ret)
{
	ft_lstclear(list, &free);
	return (ret);
}

static char	*ft_read_line_cat(t_list **list, int len)
{
	char	*str;
	t_list	*tmp;
	int		i;

	str = malloc(sizeof(char) * (len + 1));
	if (str)
	{
		tmp = *list;
		len = 0;
		while (tmp)
		{
			i = 0;
			while (((char *) tmp->content)[i])
				str[len++] = ((char *) tmp->content)[i++];
			tmp = tmp->next;
		}
		str[len] = 0;
	}
	ft_lstclear(list, &free);
	return (str);
}

static int	ft_read_line_next(t_file *file, t_list **list)
{
	int		len;
	char	*str;
	t_list	*tmp;

	len = 0;
	while (len + file->pos < FT_BUFFER_SIZE
		&& !ft_memchr("\0\n", file->buff[len + file->pos], 2))
		len++;
	if (len + file->pos < FT_BUFFER_SIZE && file->buff[len + file->pos])
		len++;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (ft_read_line_err(list, -1));
	ft_memcpy(str, file->buff + file->pos, len);
	str[len] = 0;
	tmp = ft_lstnew(str);
	if (!tmp)
		return (ft_read_line_err(list, -1));
	ft_lstadd_back(list, tmp);
	file->pos += len;
	return (len);
}

static int	ft_read_line_load_list(t_file *file, t_list **list)
{
	int		written;
	int		ret;

	written = 0;
	if (file->pos < FT_BUFFER_SIZE && file->buff[file->pos])
	{
		ret = ft_read_line_next(file, list);
		if (ret < 0)
			return (ft_read_line_err(list, ret));
		written += ret;
	}
	while ((file->pos == FT_BUFFER_SIZE && file->buff[file->pos - 1] != '\n')
		|| !written)
	{
		ret = ft_file_buffer_reload(file);
		if (ret < 0)
			return (ft_read_line_err(list, ret));
		if (!ret)
			break ;
		ret = ft_read_line_next(file, list);
		if (ret < 0)
			return (ft_read_line_err(list, ret));
		written += ret;
	}
	return (written);
}

int	ft_read_line(char **line, t_file *file)
{
	int		written;
	t_list	*list;

	*line = NULL;
	list = NULL;
	written = ft_read_line_load_list(file, &list);
	if (written <= 0)
		return (written);
	*line = ft_read_line_cat(&list, written);
	if (!*line)
		return (-1);
	return (written);
}
