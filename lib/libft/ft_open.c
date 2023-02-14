/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:48:47 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/30 16:46:33 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_open(t_file *file, const char *path, int oflag)
{
	file->fd = open(path, oflag);
	file->buff[FT_BUFFER_SIZE - 1] = 0;
	file->pos = FT_BUFFER_SIZE;
	return (file->fd);
}
