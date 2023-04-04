/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:53:57 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/04 13:54:35 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	expand_var(t_expand split[], t_env envp)
{
	int		i;
	char	**content_env[2];
	char	err;

	content_env[0] = envp.env;
	i = 0;
	while (split[i].str)
	{
		if (split[i].type == DFL || split[i].type == DBL)
		{
			content_env[1] = &split[i].str;
			err = put_var_env_elem(content_env, envp.code, 0, '\0');
			if (err)
				return (err);
		}
		i++;
	}
	return (0);
}
