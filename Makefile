SRCLIST		=	main.c\
				parser/parser.c\
				parser/parser_utils.c\
				parser/parser_get.c\
				parser/parser_env_utils_more.c\
				parser/parser_env_utils.c\
				parser/parser_env_more.c\
				parser/parser_env.c\
				parser/parser_clean.c\
				parser/parser_clean_utils.c\
				parser/parser_clean_utils_more.c\
				parser/put_var_env_heredoc.c\
				parser/list_utils.c\
				parser/gather_txt.c\
				parser/parser_get_utils.c\
				parser/space_split.c\
				parser/expand_elem.c\
				parser/expand_wildcards.c\
				parser/expand_wildcard.c\
				parser/get_wildcard_shards.c\
				parser/get_wildcard_shards_utils.c\
				parser/put_args_wildcard_block.c\
				parser/clear_split.c\
				parser/rm_quotes.c\
				parser/goto_par_end.c\
				parser/split_quotes.c\
				parser/split_quotes_utils.c\
				parser/split_fields.c\
				parser/split_fields_utils.c\
				parser/replace_content.c\
				parser/expand_var.c\
				parser/create_block.c\
				parser/free_block.c\
				search_path.c\
				builtins/cd.c\
				builtins/cd_utils.c\
				builtins/cd_more.c\
				builtins/echo.c\
				builtins/env.c\
				builtins/export.c\
				builtins/pwd.c\
				builtins/unset.c\
				builtins/exit.c\
				init_env.c\
				redirect_in.c\
				redirect_out.c\
				exec_builtin.c\
				exec_cmd.c\
				exec_simple_cmd.c\
				verif_simple_cmd.c\
				set_fd_redirect.c\
				exec_list.c\
				exec_pipeline.c\
				fill_pipeline.c\
				pipeline_init_process.c\
				exec_subshell.c\
				eval_exec.c\
				heredoc.c\
				heredoc_utils.c\
				ft_lstsize_parsing.c\
				get_status.c\
				init_shell.c\
				free_utils.c\
				check_redirection.c\
				set_portion.c\
				minishell.c
				

NAME 		=	minishell

SRCDIR		=	./src/
OBJDIR		=	./obj/
LIBDIR		=	./lib/
INCDIR		=	./inc/

LIBFT		=	$(addprefix $(LIBDIR), libft/libft.a)
LIBFT_INC	=	$(addprefix $(LIBDIR), libft/)
LIBFT_DIR	=	$(addprefix $(LIBDIR), libft/)
LIBFT_NAME	=	ft

LIBS		=	-L${LIBFT_INC} -l${LIBFT_NAME} -lreadline

INCS		=	-I${INCDIR} -I${LIBFT_INC}
SRCS		=	$(addprefix $(SRCDIR), $(SRCLIST))
OBJSLIST	=	$(SRCLIST:.c=.o)
OBJS		=	$(addprefix $(OBJDIR), $(OBJSLIST))

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

all			:	${OBJDIR} ${LIBFT} ${NAME}
bonus		:	${OBJDIR} ${LIBFT} ${NAME}

${OBJDIR}	:
		mkdir -p ${OBJDIR}builtins
		mkdir -p ${OBJDIR}parser

${OBJS}		:	${OBJDIR}%.o: ${SRCDIR}%.c
		${CC} ${CFLAGS} ${INCS} -c $< -o $@

${NAME}		:	${LIBFT} ${OBJS}
		${CC} ${CFLAGS} ${INCS} ${OBJS} -o ${NAME} ${LIBS}

${LIBFT}	:
		make -sC ${LIBFT_DIR}

clean		:
		rm -rf ${OBJDIR}
		make -sC ${LIBFT_DIR} fclean

fclean		:	clean
		rm -rf ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re bonus
