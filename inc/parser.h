/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 17:53:24 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/09 18:13:46 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>

# include <stdlib.h>

# include <libft.h>

enum e_id_char
{
	ALPHA_NUM,
	SPACE_ID,
	S_QUOTE,
	D_QUOTE,
	DOLLAR,
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

typedef struct s_parsing
{
	struct s_parsing	*next;
	struct s_parsing	*prev;
	char				*content;
	char				type;
	int					fd;
}	t_parsing;

char		parser(char *cmd, t_parsing **list_parsing, char **env);

void		ft_lstadd_back_parsing(t_parsing **lst, t_parsing *new);
t_parsing	*ft_lstlast_parsing(t_parsing *lst);
t_parsing	*ft_lstnew_parsing(char *content, char type);
char		list_parsing_clean(t_parsing *list_parsing);
void		ft_lstclear_parsing(t_parsing *list_parsing);

char		put_var_env(t_parsing **list_parsing, char **env);
char		gather_txt(t_parsing *list_parsing);
char		identify_type_char(char c);
char		get_id_cmd(char *cmd, char **id_tab);
char		second_quote(char *id_tab, int *i);
char		syntax_error_near(char *str);

char		get_space(char *id_tab, int *i, t_parsing **list_parsing);
char		get_elem_quoted(char *cmd, char *id_tab, int *i,
	t_parsing **list_parsing);
int 		get_size_elem_type(char *id_tab, int *i, char id_1, char id_2);
char		get_elem_txt(char *cmd, char *id_tab, int *i, 
	t_parsing **list_parsing);
char		get_pipe(char *cmd, char *id_tab, int *i, t_parsing **list_parsing);
char		get_redirect(char *cmd, char *id_tab, int *i,
	t_parsing **list_parsing);
char		get_var_env_txt(const char *txt, char **var);
char    get_and(char *cmd, char *id_tab, int *i, t_parsing **list_parsing);
char    get_par(char *cmd, char *id_tab, int *i, t_parsing **list_parsing);

//DEBUG
void		print_list_parsing(t_parsing *list_parsing);

#endif
