/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 08:54:51 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 11:35:35 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_conv(va_list args, t_params params, int fd)
{
	if (params.conversion == 'c')
		return (ft_printf_conv_c(params, va_arg(args, int), fd));
	else if (params.conversion == 's')
		return (ft_printf_conv_s(params, va_arg(args, const char *), fd));
	else if (params.conversion == 'p')
		return (ft_printf_conv_p(params, va_arg(args, void *), fd));
	else if (params.conversion == 'd' || params.conversion == 'i')
		return (ft_printf_conv_d(params, va_arg(args, int), fd));
	else if (params.conversion == 'u' || params.conversion == 'x'
		|| params.conversion == 'X')
		return (ft_printf_conv_o(params, va_arg(args, unsigned int), fd));
	else
		return (ft_printf_conv_other(params, fd));
}

static t_params	ft_printf_parser_flags(char **s)
{
	t_params	params;

	(*s)++;
	params.flag_padding = 0;
	params.flag_prefix = 0;
	params.flag_alternate = 0;
	while (**s == '-' || **s == '0' || **s == ' ' || **s == '+' || **s == '#')
	{
		if (**s == '-')
			params.flag_padding = '-';
		else if (**s == '0' && params.flag_padding != '-')
			params.flag_padding = '0';
		else if (**s == ' ' && params.flag_prefix != '+')
			params.flag_prefix = ' ';
		else if (**s == '+')
			params.flag_prefix = '+';
		else if (**s == '#')
			params.flag_alternate = '#';
		(*s)++;
	}
	return (params);
}

static t_params	ft_printf_parser(char **s)
{
	t_params	params;

	params = ft_printf_parser_flags(s);
	params.width = ft_atoi(*s);
	while (ft_isdigit(**s))
		(*s)++;
	params.precision = -1;
	if (**s == '.')
	{
		params.precision = ft_atoi(++(*s));
		while (ft_isdigit(**s))
			(*s)++;
	}
	params.conversion = *(*s)++;
	return (params);
}

static int	ft_printf_read(char *str, va_list args, int fd)
{
	int		written;
	char	*next;

	written = 0;
	while (str)
	{
		next = ft_strchr(str, '%');
		if (next)
			write(fd, str, next - str);
		else
			ft_putstr_fd(str, fd);
		if (next)
			written += next - str;
		else
			written += ft_strlen(str);
		str = next;
		if (str)
			written += ft_printf_conv(args, ft_printf_parser(&str), fd);
	}
	return (written);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	int		written;

	va_start(args, str);
	written = ft_printf_read((char *) str, args, fd);
	va_end(args);
	return (written);
}
