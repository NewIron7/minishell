/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 21:18:01 by ddelhalt          #+#    #+#             */
/*   Updated: 2022/11/12 12:24:17 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb && (nmemb * size) / nmemb != size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem)
		ft_bzero(mem, nmemb * size);
	return (mem);
}
