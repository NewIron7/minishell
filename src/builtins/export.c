/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 22:22:58 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/14 19:48:27 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_env(char *arg, char **envp[], int entry)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (entry + 2));
	if (!new_env)
	{
		perror("minishell: export");
		return (EXIT_FAILURE);
	}
	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[entry] = ft_strdup(arg);
	if (!new_env[entry])
	{
		free(new_env);
		perror("minishell: export");
		return (EXIT_FAILURE);
	}
	new_env[entry + 1] = NULL;
	free(*envp);
	*envp = new_env;
	return (EXIT_SUCCESS);
}

static int	update_env(char *arg, char *envp[], int entry)
{
	free(envp[entry]);
	envp[entry] = ft_strdup(arg);
	if (!envp[entry])
	{
		perror("minishell: export");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	export_env(char *arg, char **envp[], char *split)
{
	int	i;

	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], arg, split - arg + 1))
		i++;
	if ((*envp)[i])
		return (update_env(arg, *envp, i));
	else
		return (add_env(arg, envp, i));
}

int	builtin_export(char *const argv[], char **envp[])
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
			ret = (ret || export_env(*argv, envp, split));
	}
	return (ret);
}
