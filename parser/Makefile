# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MakefileTemplate                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/12 15:13:46 by tbelleng          #+#    #+#              #
#    Updated: 2023/01/20 14:37:41 by hboissel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser

SRC_DIR = src

BIN_DIR = bin

SRC = $(SRC_DIR)/ft_strjoin.c				\
      $(SRC_DIR)/ft_strlen.c					\
      $(SRC_DIR)/ft_strtrim.c				\
      $(SRC_DIR)/main.c						\
      $(SRC_DIR)/list_utils.c						\
      $(SRC_DIR)/parser.c						\
      $(SRC_DIR)/ft_strdup.c						\
      $(SRC_DIR)/parser_env.c						\

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(BIN_DIR)/%.o)

INCLUDES = ./inc

CFLAGS = -Werror -Wextra -Wall -I$(INCLUDES) -g3

all :	$(NAME)


$(BIN_DIR):
		@ mkdir -p $(BIN_DIR)

$(OBJ) :		$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(BIN_DIR)
		@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME) :	$(OBJ)
			@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME)
			@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

clean :
		@ rm -f $(OBJ)
		@ rm -rf $(BIN_DIR)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
		@ rm -f $(NAME)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"

re :fclean
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRecompile .. 🔄"
	@ $(MAKE) -s $(NAME)

.PHONY: all clean fclean re
