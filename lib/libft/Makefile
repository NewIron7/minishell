# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/07 09:48:13 by ddelhalt          #+#    #+#              #
#    Updated: 2023/03/28 20:00:57 by ddelhalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRCS		=	ft_isalpha.c\
				ft_isdigit.c\
				ft_isalnum.c\
				ft_isascii.c\
				ft_isprint.c\
				ft_isspace.c\
				ft_strlen.c\
				ft_memset.c\
				ft_bzero.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_strlcpy.c\
				ft_strlcat.c\
				ft_toupper.c\
				ft_tolower.c\
				ft_strchr.c\
				ft_strrchr.c\
				ft_strncmp.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_strnstr.c\
				ft_atoi.c\
				ft_calloc.c\
				ft_strdup.c\
				ft_substr.c\
				ft_strjoin.c\
				ft_strtrim.c\
				ft_split.c\
				ft_itoa.c\
				ft_strmapi.c\
				ft_striteri.c\
				ft_putchar_fd.c\
				ft_putstr_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c\
				get_next_line.c\
				ft_max.c\
				ft_min.c\
				ft_putunbr_base_fd.c\
				ft_putunbr_fd.c\
				ft_printf_fd.c\
				ft_printf_conv_c.c\
				ft_printf_conv_d.c\
				ft_printf_conv_o.c\
				ft_printf_conv_p.c\
				ft_printf_conv_s.c\
				ft_printf_conv_other.c\
				ft_printf_padding.c\
				ft_printf.c\
				ft_open.c\
				ft_close.c\
				ft_read_line.c\
				ft_file_buffer_reload.c\
				ft_basename.c\
				ft_strcmp.c\
				ft_abs.c\
				ft_strstr.c\
				ft_dynalloc.c

OBJS		=	$(SRCS:%.c=%.o)

CFLAGS		=	-Wall -Wextra -Werror

CC			=	cc

AR			=	ar

RM			=	rm -f

all				:	$(NAME)

$(NAME)			:	$(OBJS)
	$(AR) rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJS)			:	%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean			:
	$(RM) $(OBJS)

fclean			:	clean
	$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
