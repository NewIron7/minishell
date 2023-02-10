/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:18:20 by hboissel          #+#    #+#             */
/*   Updated: 2023/01/30 11:10:32 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cd.h"

char	ft_cd(char *path)
{
	int	err;
	DIR *dir;

	err = 0;
	if (path)
	{
		dir = opendir(path);
		if (!dir)
		{
			err = open(path, O_RDONLY);
			if (err > 0)
			{
				close(err);
				printf("cd: not a directory: %s\n", path);
			}
			else
				printf("cd: no such file or directory: %s\n", path);
			return (1);
		}
		closedir(dir);
		err = chdir(path);
	}
	if (err)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	ft_cd(argv[1]);
	//printf("%s\n", getcwd(NULL, 0));
	return (0);
}
