/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_o.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:14:03 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:53:35 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_nb_len(unsigned int nb, int conversion)
{
	int	len;
	int	base;

	if (conversion == 'u')
		base = 10;
	else
		base = 16;
	len = 0;
	while (nb)
	{
		len++;
		nb /= base;
	}
	return (len);
}

static t_params	ft_printf_params_o(t_params p, unsigned int n, char **s, int *b)
{
	if (p.flag_padding == '0' && p.precision >= 0)
		p.flag_padding = 0;
	if (p.precision == -1)
		p.precision = 1;
	*b = (p.conversion != 'u' && p.flag_alternate && n) * 2;
	if (p.conversion == 'u')
		*s = "0123456789";
	else if (p.conversion == 'x')
		*s = "0123456789abcdef";
	else
		*s = "0123456789ABCDEF";
	return (p);
}

int	ft_printf_conv_o(t_params params, unsigned int arg, int fd)
{
	int		nb_len;
	int		written;
	int		i;
	int		prefix;
	char	*base;

	written = 0;
	params = ft_printf_params_o(params, arg, &base, &prefix);
	nb_len = ft_printf_nb_len(arg, params.conversion);
	written += ft_printf_padding(params.width
			- ft_max(params.precision, nb_len) - prefix, params, prefix, fd);
	i = 0;
	while (params.precision - i++ > nb_len)
		ft_putchar_fd('0', fd);
	written += i - 1;
	if (arg)
	{
		ft_putunbr_base_fd(arg, base, fd);
		written += nb_len;
	}
	written += ft_printf_padding(params.width
			- ft_max(params.precision, nb_len) - prefix, params, -1, fd);
	return (written);
}
