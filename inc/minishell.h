/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:14:25 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/04/05 14:23:00 by ddelhalt         ###   ########.fr       */
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

typedef struct s_process
{
	t_parsing	**parsing;
	t_portion	chunck;
	int			to_fork;
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
int			exec_builtin(char *cmd[], t_env *envp,
				t_process *process, t_list **pipeline);
int			exec_cmd(char *argv[], char *envp[],
				t_process *process, t_list **pipeline);
int			redirect_in(int fd);
int			redirect_out(int fd);
char		*search_path(char *cmd, char **env, char *var);
void		eval_exec(t_parsing **parsing, t_portion chunck, t_env *envp,
				t_list **pipeline);
void		exec_list(t_parsing **parsing, t_portion chunck, t_env *envp,
				t_list **pipeline);
void		exec_pipeline(t_parsing **parsing, t_portion chunck, t_env *envp,
				t_list **pipeline);
void		fill_pipeline(t_parsing **parsing,
				t_portion chunck, t_list **pipeline);
int			pipeline_init_process(t_portion chunck, t_list **pipeline,
				int infile, int outfile);
void		exec_simple_cmd(t_process *process, t_env *envp, t_list **pipeline);
char		ft_heredoc(t_parsing *tokens);
int			ft_lstsize_parsing(t_parsing *tokens);
char		is_builtin(char *argv[]);
char		set_fd_redirect(int *fd_in, int *fd_out, t_parsing *tokens,
				int redirs);
int			verif_simple_cmd(t_process *process, t_env *envp, char ***args);
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
int			size_dir(char *path);
char		*get_pwd(char **env);
char		exec_cd(char *path, char cdpath);
char		rm_current_dir(char **path, int *i, int size);
char		rm_prev_dir(char **path, int *i);
char		clean_path(char **path);
char		add_pwd(char **path, char **env);
char		do_change_env_pwd(char **env[], char *oldpwd, char *newpwd);
char		do_change_env(char **env[]);
int			check_redirection(t_portion chunck);
t_portion	set_portion(t_parsing *start, t_parsing *end);

int			builtin_cd(char *const argv[], char **env[]);
int			builtin_echo(char *const argv[], int fd);
int			builtin_env(char *const envp[], int fd);
int			builtin_export(char *const argv[], char **envp[]);
int			builtin_pwd(int fd);
int			builtin_unset(char *const argv[], char *envp[]);
int			builtin_exit(char *argv[], t_env envp, t_parsing *pars,
				t_list **pipeline);

#endif
