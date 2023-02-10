/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 19:02:49 by hboissel          #+#    #+#             */
/*   Updated: 2023/02/09 16:10:58 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"
/*
static void	print_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}*/

int	main(int argc, char **argv, char **env)
{
	t_parsing	*list_parsing;

	(void)argc;
	//print_env(env);
	parser(argv[1], &list_parsing, env);
	return (0);
}
