/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:14:25 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/01 23:47:33 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "parser.h"
# include "get_next_line.h"
# include <sys/stat.h>
# include <signal.h>

enum e_mode
{
	INTERACTIVE,
	EXEC
};

extern t_list	*g_cpids;

void	init_env(char **envp[]);
void	free_env(char *envp[]);
void	main_loop(char **envp[]);
int		exec_builtin(char *cmd[], char **envp[], int fd_in, int fd_out);
int		exec_cmd(char *argv[], char *envp[], int fd_in, int fd_out);
int		redirect_in(int fd);
int		redirect_out(int fd);
char	*search_path(char *cmd, char **env);
int		minishell_init(char **envp[]);

int		builtin_cd(char *const argv[]);
int		builtin_echo(char *const argv[], int fd);
int		builtin_env(char *const envp[], int fd);
int		builtin_export(char *const argv[], char **envp[]);
int		builtin_pwd(void);
int		builtin_unset(char *const argv[], char *envp[]);
int		builtin_exit(char *const argv[], char *envp[]);

#endif
