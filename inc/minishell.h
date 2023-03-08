/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:14:25 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/08 20:06:20 by ddelhalt         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>

enum e_mode
{
	INTERACTIVE,
	EXEC
};

typedef struct s_subtokens
{
	t_parsing	*tokens;
	int			start;
	int			sep;
	int			end;
}	t_subtokens;

extern t_list	*g_cpids;

void		init_env(char **envp[]);
void		free_env(char *envp[]);
void		main_loop(char **envp[]);
int			exec_builtin(char *cmd[], char **envp[], int fd_in, int fd_out);
int			exec_cmd(char *argv[], char *envp[], int fd_in, int fd_out);
int			redirect_in(int fd);
int			redirect_out(int fd);
char		*search_path(char *cmd, char **env);
int			minishell_init(char **envp[]);
int			eval_exec(t_subtokens tokens, char **envp[]);
int			exec_list(t_subtokens tokens, char **envp[]);
int			add_pid_glob(int pid);
int			exec_pipe(t_subtokens tokens, char **envp[]);
int			exec_simple_cmd(t_subtokens tokens, char **envp[]);
char		ft_heredoc(t_parsing *tokens);
int			ft_lstsize_parsing(t_parsing *tokens);
char		is_builtin(char *argv[]);
char    	get_exec_path(char *cmd);
char    	put_new_fd_redirec(t_parsing *tokens, int *fd_out, int *fd_in);
char    	is_redirection(t_parsing *tokens);
t_subtokens	subtokens_init(t_parsing *tokens, int start, int sep, int end);

int		builtin_cd(char *const argv[]);
int		builtin_echo(char *const argv[], int fd);
int		builtin_env(char *const envp[], int fd);
int		builtin_export(char *const argv[], char **envp[]);
int		builtin_pwd(void);
int		builtin_unset(char *const argv[], char *envp[]);
int		builtin_exit(char *const argv[], char *envp[]);

#endif
