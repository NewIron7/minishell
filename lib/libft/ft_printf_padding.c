/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_padding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:25:57 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:59:09 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printf_padding_prefix(int pos, t_params params, int sign, int fd)
{
	if ((sign == 1 || sign == 3) && (params.flag_padding == '0') == pos)
		ft_putchar_fd(params.flag_prefix, fd);
	if ((sign == 2 || sign == 3) && (params.flag_padding == '0') == pos)
	{
		ft_putchar_fd('0', fd);
		if (params.conversion == 'p')
			ft_putchar_fd('x', fd);
		else
			ft_putchar_fd(params.conversion, fd);
	}
}

int	ft_printf_padding(int size, t_params params, int sign, int fd)
{
	int	written;

	written = ft_max(sign, 0);
	ft_printf_padding_prefix(1, params, sign, fd);
	if ((params.flag_padding != '-' && sign >= 0)
		|| (params.flag_padding == '-' && sign < 0))
	{
		while (size-- > 0)
		{
			if (params.flag_padding == '0')
				ft_putchar_fd('0', fd);
			else
				ft_putchar_fd(' ', fd);
			written++;
		}
	}
	ft_printf_padding_prefix(0, params, sign, fd);
	return (written);
}
