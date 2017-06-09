# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/06/09 05:08:24 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

DIR_LFT = libft/
DIR_MLXJI = libmlxji/
DIR_MLX = minilibx_macos/
DIR_LIB = lib/

FLAGS = -Wall -Werror -Wextra -g -I ./include/

FRAMEWORK = -framework OpenGL -framework AppKit -framework Opencl

SRC_PS = main.c \
		 init_mlx.c \
		 draw.c \
		 loop.c \
		 end_of_program.c \
		 event/event_key_off.c \
		 event/event_key_on.c \
		 event/event_mouse.c \
		 event/event_move_mouse.c \
		 cl/cl_draw.c \
		 cl/cl_check_err.c \
		 cl/cl_end_opencl.c \
		 cl/cl_init_opencl.c

SRC_GRAPH =

SRC_DIR = srcs/

CC = gcc

INC = includes/

INC_FILES = includes/fractol.h \
			includes/mlx.h

OBJET = $(SRC_PS:.c=.o)

OBJ_DIR = objs/

.PHONY: all, clean, fclean, re, $(NAME), lft, start, end

all: lib $(NAME)

$(NAME): $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJET)) $(INC_FILES)
	@$(CC) -I$(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LIB) -lft -lmlx -lmlxji  $(FRAMEWORK) -o $(NAME)
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/cl
	@mkdir $(OBJ_DIR)/event

$(OBJ_GRAPH) :
	@mkdir $(OBJ_GRAPH)

start:
	@echo "\033[4m\033[33mCreation de $(NAME)   ...\033[0m"

end:
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	@echo "\033[34m$^ \033[0m-> \033[1m\033[37m$@\033[0m"
	@($(CC) $(FLAGS)  -I./$(INC) -c -o $@ $<)

lib:
	@(mkdir lib)
	@(cd $(DIR_LFT) && $(MAKE))
	@(mv $(DIR_LFT)libft.a ./lib/)
	@(cd $(DIR_MLXJI) && $(MAKE))
	@(mv $(DIR_MLXJI)libmlxji.a ./lib/)
	@(cd $(DIR_MLX) && $(MAKE))
	@(mv $(DIR_MLX)libmlx.a ./lib/)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@(cd $(DIR_LFT) && make clean)
	@(cd $(DIR_MLXJI) && make clean)
	@(cd $(DIR_MLX) && make clean)

fclean: clean
	@/bin/rm -f $(NAME)
	@(cd $(DIR_LFT) && make fclean)
	@(cd $(DIR_MLXJI) && make fclean)
	@(rm -rf lib)

re: fclean all
