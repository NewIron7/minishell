/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:24:12 by hboissel          #+#    #+#             */
/*   Updated: 2023/01/26 17:58:14 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "echo.h"

void	builtins_echo(char **str, char op)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s", str[i]);
		i++;
		if (str[i])
			printf(" ");
	}
	if (op)
		printf("\n");
}
