SRCLIST		=	main.c\
				builtins/cd.c\
				builtins/echo.c\
				builtins/env.c\
				builtins/export.c\
				builtins/pwd.c\
				builtins/unset.c

NAME 		=	minishell

SRCDIR		=	./src/
OBJDIR		=	./obj/
LIBDIR		=	./lib/
INCDIR		=	./inc/

LIBFT		=	$(addprefix $(LIBDIR), libft/libft.a)
LIBFT_INC	=	$(addprefix $(LIBDIR), libft/)
LIBFT_DIR	=	$(addprefix $(LIBDIR), libft/)
LIBFT_NAME	=	ft

LIBS		=	-L${LIBFT_INC} -l${LIBFT_NAME}

INCS		=	-I${INCDIR} -I${LIBFT_INC}
SRCS		=	$(addprefix $(SRCDIR), $(SRCLIST))
OBJSLIST	=	$(SRCLIST:.c=.o)
OBJS		=	$(addprefix $(OBJDIR), $(OBJSLIST))

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-g3

all			:	${OBJDIR} ${LIBFT} ${NAME}

${OBJDIR}	:
		mkdir -p ${OBJDIR}builtins

${OBJS}		:	${OBJDIR}%.o: ${SRCDIR}%.c
		${CC} ${CFLAGS} ${INCS} -c $< -o $@

${NAME}		:	${LIBFT} ${OBJS}
		${CC} ${CFLAGS} ${INCS} ${OBJS} -o ${NAME} ${LIBS}

${LIBFT}	:
		make -sC ${LIBFT_DIR}

debug		:	${LIBFT} ${OBJS}
		${CC} ${DEBUG} ${CFLAGS} ${INCS} ${OBJS} -o ${NAME} ${LIBS}
clean		:
		rm -rf ${OBJDIR}
		make -sC ${LIBFT_DIR} fclean

fclean		:	clean
		rm -rf ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re debug
