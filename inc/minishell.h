/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:14:25 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/03/28 18:30:08 by ddelhalt         ###   ########.fr       */
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

typedef struct s_process
{
	t_subtokens	tokens;
	pid_t		pid;
	char		killed;
	int			status;
	int			infile;
	int			outfile;
}	t_process;

void		sig_handler(int sig);
int			init_env(char **envp[]);
void		free_env(char *envp[]);
void		main_loop(void);
int			exec_builtin(char *cmd[], char **envp[],
				t_process *process, t_list **pipeline);
int			exec_cmd(char *argv[], char *envp[],
				t_process *process, t_list **pipeline);
int			redirect_in(int fd);
int			redirect_out(int fd);
char		*search_path(char *cmd, char **env, char *var);
void		eval_exec(t_subtokens tokens, t_env *envp,
				t_list **pipeline);
void		exec_list(t_subtokens tokens, t_env *envp,
				t_list **pipeline);
void		exec_pipeline(t_subtokens tokens, t_env *envp,
				t_list **pipeline);
void		fill_pipeline(t_subtokens tokens, t_list **pipeline);
int			pipeline_init_process(t_subtokens tokens, t_list **pipeline,
				int infile, int outfile);
void		exec_simple_cmd(t_process *process, t_env *envp,
				int need_fork, t_list **pipeline);
char		ft_heredoc(t_parsing *tokens);
int			ft_lstsize_parsing(t_parsing *tokens);
char		is_builtin(char *argv[]);
char		set_fd_redirect(int *fd_in, int *fd_out, t_parsing *tokens,
				int redirs);
int			verif_simple_cmd(t_process *process, t_parsing *tokens,
				t_env *envp, char ***args);
t_subtokens	subtokens_init(t_parsing *tokens, int start,
				int sep, int end);
int			get_status(int status);
void		init_shell(char **envp[]);
int			is_pipeline_sigint(t_list *pipeline);
int			pipeline_status(t_list *pipeline);
t_list		**free_pipeline(t_list **pipeline);
void		free_all(t_parsing *pars, char *envp[],
				t_list **pipeline, char **args);
void		exec_subshell(t_process *process, t_env *envp,
				t_list **pipeline);
int			get_shell_code(t_list *pipeline);
char		**exp_cmd_wild(char *str);
int			fill_split(char **str, int i, char ***split);
char		*check_cpy(char *cpy);
int			count_split(char *str);
char		check_ctrl_d(char *line, char *end);

int			builtin_cd(char *const argv[], char **env[]);
int			builtin_echo(char *const argv[], int fd);
int			builtin_env(char *const envp[], int fd);
int			builtin_export(char *const argv[], char **envp[]);
int			builtin_pwd(void);
int			builtin_unset(char *const argv[], char *envp[]);
int			builtin_exit(char *argv[], char *envp[], t_parsing *pars,
				t_list **pipeline);

#endif
