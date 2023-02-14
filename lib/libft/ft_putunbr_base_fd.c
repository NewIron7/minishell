/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:19:40 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/28 12:52:04 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_powerbase(unsigned int n, int base)
{
	unsigned int	res;

	res = 1;
	while (n-- > 1)
		res *= base;
	return (res);
}

static int	ft_nb_len(unsigned int n, unsigned int base)
{
	int	len;

	len = 1;
	while (n >= base)
	{
		len ++;
		n /= base;
	}
	return (len);
}

void	ft_putunbr_base_fd(unsigned int n, char *base, int fd)
{
	unsigned int	len;
	unsigned int	base_size;

	base_size = ft_strlen(base);
	len = ft_powerbase(ft_nb_len(n, base_size), base_size);
	while (len)
	{
		ft_putchar_fd(base[n / len], fd);
		n %= len;
		len /= base_size;
	}
}
