/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 07:30:39 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/01/22 09:24:36 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_dynalloc(void *ptr, size_t nmemb, size_t add, size_t size)
{
	void	*tmp;

	tmp = calloc(nmemb + add, size);
	if (!tmp)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		ft_memmove(tmp, ptr, nmemb * size);
		free(ptr);
	}
	return (tmp);
}
