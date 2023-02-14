/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:45:52 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:53:29 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_nb_len(int nb)
{
	int	len;

	len = 0;
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

static unsigned int	ft_printf_itou(int n)
{
	if (n < 0)
		return ((unsigned int) -n);
	return ((unsigned int) n);
}

static t_params	ft_printf_params_d(t_params params, int arg)
{
	if (params.flag_padding == '0' && params.precision >= 0)
		params.flag_padding = 0;
	if (params.precision == -1)
		params.precision = 1;
	if (arg < 0)
		params.flag_prefix = '-';
	return (params);
}

int	ft_printf_conv_d(t_params params, int arg, int fd)
{
	int	nb_len;
	int	written;
	int	sign;
	int	i;
	int	padding;

	written = 0;
	params = ft_printf_params_d(params, arg);
	sign = params.flag_prefix != 0;
	nb_len = ft_printf_nb_len(arg);
	if (!arg && params.precision)
		nb_len = 1;
	padding = params.width - ft_max(params.precision, nb_len) - sign;
	written += ft_printf_padding(padding, params, sign, fd);
	i = 0;
	while (params.precision - i++ - nb_len > 0)
	{
		ft_putchar_fd('0', fd);
		written++;
	}
	if (arg || params.precision)
		ft_putunbr_fd(ft_printf_itou(arg), fd);
	written += nb_len;
	written += ft_printf_padding(padding, params, -1, fd);
	return (written);
}
