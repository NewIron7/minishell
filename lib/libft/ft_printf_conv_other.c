/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_other.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:40:03 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:53:42 by ddelhalt         ###   ########.fr       */
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

static int	ft_printf_putchar(int c, int fd)
{
	ft_putchar_fd(c, fd);
	return (1);
}

int	ft_printf_conv_other(t_params params, int fd)
{
	int	written;

	ft_putchar_fd('%', fd);
	written = 1;
	if (params.conversion == '%')
		return (written);
	if (params.flag_alternate)
		written += ft_printf_putchar('#', fd);
	if (params.flag_prefix)
		written += ft_printf_putchar(params.flag_prefix, fd);
	if (params.flag_padding)
		written += ft_printf_putchar(params.flag_alternate, fd);
	if (params.width)
	{
		ft_putnbr_fd(params.width, fd);
		written += ft_printf_nb_len(params.width);
	}
	if (params.precision)
	{
		written += ft_printf_putchar('.', fd);
		ft_putnbr_fd(params.precision, fd);
		written += ft_printf_nb_len(params.precision);
	}
	written += ft_printf_putchar(params.conversion, fd);
	return (written);
}
