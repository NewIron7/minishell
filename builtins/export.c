/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:22:58 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/13 22:44:03 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_env(char *arg, char *envp[], int entry)
{
	char	*new_env;

	new_env = malloc(sizeof(char *) * (entry + 1));
	if (!new_env)
	{
		perror("minishell: export");
		return (EXIT_FAILURE);
	}
	ft_memcpy(new_env, envp, sizeof(char *) * (entry - 1));
	new_env[entry] = ft_strdup(arg);
	if (!new_env[entry])
	{
		free(new_env);
		perror("minishell: export");
		return (EXIT_FAILURE);
	}
	new_env[entry + 1] = NULL;
	free(envp);
	envp = new_env;
}

static int	update_env(char *arg, char *envp[], int entry)
{
	free(envp[i]);
	envp[i] = ft_strdup(arg);
	if (!envp[i])
	{
		perror("minishell: export");
		return (EXIT_FAILURE);
	}
}

int	export_env(char *arg, char *envp[], int entry)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], *argv, split - *argv + 1))
		i++;
	if (envp[i])
		return (update_env(*argv, envp, i));
	else
		return (add_env(*argv, envp, i));
}

int	builtin_export(char *const argv[], char *envp[])
{
	int		ret;
	char	*split;

	ret = 0;
	while (*++argv)
	{
		split = ft_strchr(*argv, '=');
		if (split == *argv)
		{
			ret = 1;
			ft_printf_fd(2,
				"minishell: export: `%s': not a valid identifier\n", *argv);
		}
		else if (split)
			ret = (ret || export_env(*argv, envp, i));
	}
	return (ret);
}
