/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 08:20:07 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:52:25 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(unsigned int n)
{
	int	len;

	len = 1;
	while (n >= 10)
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

void	ft_putunbr_fd(unsigned int n, int fd)
{
	int	len;

	len = ft_nbrlen(n);
	len = ft_power10(len);
	while (len)
	{
		ft_putchar_fd(n / len + '0', fd);
		n %= len;
		len /= 10;
	}
}
