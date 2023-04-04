/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:29:14 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/04 19:33:35 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	create_block(t_list **block, t_expand split[])
{
	*block = ft_lstnew(split);
	if (*block == NULL)
		return (1);
	return (0);
}
