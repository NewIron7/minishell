/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv_p.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:28:44 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:53:48 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_nb_len(uintptr_t nb)
{
	int	len;

	len = 0;
	while (nb)
	{
		len++;
		nb /= 16;
	}
	return (len);
}

static void	ft_putulnbr_base_fd(uintptr_t n, char *base, int fd)
{
	uintptr_t	power;
	int			nb_len;

	nb_len = ft_printf_nb_len(n);
	power = 1;
	while (nb_len-- > 1)
		power *= 16;
	while (power)
	{
		ft_putchar_fd(base[n / power], fd);
		n %= power;
		power /= 16;
	}
}

static t_params	ft_printf_params_p(t_params params, void *arg, uintptr_t *p)
{
	*p = (uintptr_t) arg;
	if (params.flag_padding == '0' && (params.precision >= 0 || !arg))
		params.flag_padding = 0;
	if (params.precision == -1)
		params.precision = 1;
	if (!arg)
		params.precision = -1;
	return (params);
}

int	ft_printf_conv_p(t_params params, void *arg, int fd)
{
	uintptr_t	p;
	int			written;
	int			nb_len;
	int			i;
	int			width;

	written = 0;
	params = ft_printf_params_p(params, arg, &p);
	if (!arg)
		return (ft_printf_conv_s(params, "(nil)", fd));
	nb_len = ft_printf_nb_len(p);
	width = params.width - ft_max(params.precision, nb_len)
		- 2 - (params.flag_prefix != 0);
	written += ft_printf_padding(width, params,
			(params.flag_prefix != 0) + 2, fd);
	i = 0;
	while (params.precision - i++ > nb_len)
		ft_putchar_fd('0', fd);
	written += i - 1;
	ft_putulnbr_base_fd(p, "0123456789abcdef", fd);
	written += nb_len;
	written += ft_printf_padding(width, params, -1, fd);
	return (written);
}
