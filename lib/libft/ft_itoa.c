/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 06:22:48 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/01/03 08:46:05 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(int n)
{
	size_t	len;

	len = 1;
	while (n >= 10 || n <= -10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		sign;
	size_t	len;
	char	*str;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = ft_nbrlen(n);
	str = malloc(len + sign + 1);
	if (!str)
		return (NULL);
	str[sign + len] = 0;
	while (len--)
	{
		str[sign + len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
