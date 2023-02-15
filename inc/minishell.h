/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:14:25 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/15 09:35:19 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "libft.h"

char	**init_env(char *envp[]);
void	free_env(char *envp[]);

int	builtin_cd(char *const argv[]);
int	builtin_echo(char *const argv[]);
int	builtin_env(char *const envp[]);
int	builtin_export(char *const argv[], char **envp[]);
int	builtin_pwd(void);
int	builtin_unset(char *const argv[], char *envp[]);

#endif
