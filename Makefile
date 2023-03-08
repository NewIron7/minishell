SRCLIST		=	main.c\
				parser/parser.c\
				parser/parser_utils.c\
				parser/parser_quote.c\
				parser/parser_print.c\
				parser/parser_get.c\
				parser/parser_env_utils.c\
				parser/parser_env.c\
				parser/parser_clean.c\
				parser/list_utils.c\
				parser/gather_txt.c\
				search_path.c\
				builtins/cd.c\
				builtins/echo.c\
				builtins/env.c\
				builtins/export.c\
				builtins/pwd.c\
				builtins/unset.c\
				builtins/exit.c\
				env_handler.c\
				redirect_in.c\
				redirect_out.c\
				exec_builtin.c\
				exec_cmd.c\
				exec_simple_cmd.c\
				exec_simple_cmd_utils.c\
				exec_list.c\
				exec_pipe.c\
				minishell_init.c\
				add_pid_glob.c\
				eval_exec.c\
				heredoc.c\
				ft_lstsize_parsing.c\
				search_path_utils.c \
				subtokens_init.c\
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
CFLAGS		=	-Wall -Wextra -Werror -g3
DEBUG		=	-g3

all			:	${OBJDIR} ${LIBFT} ${NAME}

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

.PHONY		:	all clean fclean re
