/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:14:25 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/02/28 19:37:50 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "parser.h"

char	**init_env(char *envp[]);
void	free_env(char *envp[]);
void	main_loop(char **envp[]);
int		exec_builtin(char *cmd[], char **envp[], int fd_in, int fd_out);
int		exec_cmd(char *argv[], char *envp[], int fd_in, int fd_out);
int		redirect_in(int fd);
int		redirect_out(int fd);
char	*search_path(char *cmd, char **env);

int		builtin_cd(char *const argv[]);
int		builtin_echo(char *const argv[], int fd);
int		builtin_env(char *const envp[], int fd);
int		builtin_export(char *const argv[], char **envp[]);
int		builtin_pwd(void);
int		builtin_unset(char *const argv[], char *envp[]);
int		builtin_exit(char *const argv[], char *envp[]);

#endif
