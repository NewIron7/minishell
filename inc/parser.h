/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:53:24 by hboissel          #+#    #+#             */
/*   Updated: 2023/04/03 16:32:45 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>

# include <stdlib.h>

# include <libft.h>

# include <dirent.h>

enum e_id_char
{
	ALPHA_NUM,
	SPACE_ID,
	PIPE_C,
	REDIRECT,
	AND_ID,
	PAR
};

enum e_id_elem
{
	CMD,
	ARG,
	PIPE,
	R_INPUT,
	R_OUTPUT,
	R_DINPUT,
	R_DOUTPUT,
	REDIRECT_TMP,
	SPACE_TMP,
	TXT,
	TXT_S,
	TXT_D,
	AND,
	OR,
	PAR_TMP,
	LEFT_PAR,
	RIGHT_PAR
};

enum e_quote_type
{
	DFL,
	SPL,
	DBL
};

typedef struct s_parsing
{
	struct s_parsing	*next;
	struct s_parsing	*prev;
	char				*content;
	char				type;
	int					fd;
	char				quoted;
}	t_parsing;

typedef struct s_env
{
	char	**env;
	int		code;
}	t_env;

typedef struct s_portion
{
	t_parsing	*start;
	t_parsing	*end;
}	t_portion;

typedef struct s_expand
{
	char	*str;
	int		type;
}	t_expand;

char		parser(char *cmd, t_parsing **list_parsing);

char		rm_quotes(char *str);
char		check_env_heredoc(t_portion chunck, t_env env);
void		ft_lstadd_back_parsing(t_parsing **lst, t_parsing *new);
t_parsing	*ft_lstlast_parsing(t_parsing *lst);
t_parsing	*ft_lstnew_parsing(char *content, char type);
char		list_parsing_clean(t_parsing *list_parsing);
void		ft_lstclear_parsing(t_parsing *list_parsing);
char		ft_strcmp_parsing(char *str1, char *str2);
char		unvalid_token(t_parsing *tokens);
char		verif_and(t_parsing *list_parsing);
char		verif_pipe(t_parsing *list_parsing);
char		is_par(char *str, char par);
char		verif_par_tmp(t_parsing *list_parsing);
char		is_redirect(t_parsing *token);
char		is_cmd_arg(t_parsing *token);
char		is_and_pipe_or(t_parsing *token);
char		get_value_var(char *var, char **env, char **value, int code);
int			insert_value_var(char **content, char *value,
				int *len_var, int *i);
char		put_var_env_elem(char **content_env[], int code,
				int start, char end);
char		am_i_in_dbl(char *str, int n);
char		move_right_part(char *str);
char		put_var_quote(char **content_env[], int code, int n);
char		check_var_env_txt(char **content_env[], char **var,
				int *len_var, int i);
char		check_quote(char **next, const char *str, int n, char *quote);

char		put_var_env(t_portion chunck, t_env envp);
char		gather_txt(t_parsing *list_parsing);
char		identify_type_char(char c);
char		get_id_cmd(char *cmd, char **id_tab);
char		second_quote(char *id_tab, int *i);
char		syntax_error_near(char *str);
char		is_char_var_env(char c);

char		get_space(char *id_tab, int *i, t_parsing **list_parsing);
char		get_elem_quoted(char *cmd, char *id_tab, int *i,
				t_parsing **list_parsing);
int			get_size_elem_type(char *id_tab, int *i, char id_1, char id_2);
char		get_elem_txt(char *cmd, char *id_tab, int *i,
				t_parsing **list_parsing);
char		get_pipe(char *cmd, char *id_tab, int *i, t_parsing **list_parsing);
char		get_redirect(char *cmd, char *id_tab, int *i,
				t_parsing **list_parsing);
char		get_var_env_txt(const char *txt, char **var);
char		get_and(char *cmd, char *id_tab, int *i, t_parsing **list_parsing);
char		get_par(char *cmd, char *id_tab, int *i, t_parsing **list_parsing);
int			expand_elem(t_parsing *elem, int (*splitter)(char *, char ***));
int			space_split(char *str, char ***split);
int			expand_wildcard(char *str, char ***split);
char		skip_subshells(t_parsing **elem);
int			get_wildcard_shards(char *str, char ***shards);
void		clear_split(char ***split);
t_parsing	*goto_par_end(t_parsing *parsing);
int			split_quotes(t_expand *split[], char *content);

//DEBUG
void		print_list_parsing(t_parsing *list_parsing);

#endif
