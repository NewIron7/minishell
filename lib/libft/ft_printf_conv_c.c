/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_c.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:15:11 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:53:21 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_conv_c(t_params params, int arg, int fd)
{
	int	written;

	written = 0;
	if (params.flag_padding == '0')
		params.flag_padding = 0;
	if (params.flag_padding != '-')
		written += ft_printf_padding(params.width - 1, params, 0, fd);
	ft_putchar_fd((unsigned char) arg, fd);
	written++;
	if (params.flag_padding == '-')
		written += ft_printf_padding(params.width - 1, params, -1, fd);
	return (written);
}
