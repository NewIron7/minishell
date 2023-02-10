/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:54:33 by hboissel          #+#    #+#             */
/*   Updated: 2023/01/30 10:13:53 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pwd.h"

char	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	main(void)
{
	ft_pwd();
	return (0);
}
