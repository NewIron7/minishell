/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:20:07 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/01/03 08:46:20 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	len;

	len = 1;
	while (n >= 10 || n <= -10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static int	ft_power10(int n)
{
	int	res;

	res = 1;
	while (n-- > 1)
		res *= 10;
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	len;

	if (n < 0)
		ft_putchar_fd('-', fd);
	len = ft_nbrlen(n);
	len = ft_power10(len);
	while (len)
	{
		ft_putchar_fd(ft_abs(n / len) + '0', fd);
		n %= len;
		len /= 10;
	}
}
