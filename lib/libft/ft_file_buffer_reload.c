/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_buffer_reload.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:26:04 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/12/01 08:28:37 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_file_buffer_reload(t_file *file)
{
	int	i;

	i = read(file->fd, file->buff, FT_BUFFER_SIZE);
	if (i < 0)
		return (i);
	file->pos = 0;
	if (i < FT_BUFFER_SIZE)
		file->buff[i] = 0;
	return (i);
}
