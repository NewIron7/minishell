/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:14:12 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:53:54 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_params	ft_printf_params_s(t_params params, const char **arg)
{
	if (!*arg)
	{
		if (params.precision == -1 || params.precision >= 6)
			*arg = "(null)";
		else
			*arg = "";
	}
	if (params.flag_padding == '0')
		params.flag_padding = 0;
	return (params);
}

int	ft_printf_conv_s(t_params params, const char *arg, int fd)
{
	int	len;
	int	written;

	written = 0;
	params = ft_printf_params_s(params, &arg);
	len = ft_strlen(arg);
	if (params.precision >= 0)
		len = ft_min(params.precision, len);
	written += ft_printf_padding(params.width - len, params, 0, fd);
	write(fd, arg, len);
	written += len;
	written += ft_printf_padding(params.width - len, params, -1, fd);
	return (written);
}
