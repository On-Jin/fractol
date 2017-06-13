# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/06/13 16:27:16 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

DIR_LFT = libft/
DIR_MLXJI = libmlxji/
DIR_MLX = minilibxcaptain/
DIR_LIB = all_lib/

FLAGS = -Wall -Werror -Wextra -g -I ./include/

FRAMEWORK = -framework OpenGL -framework AppKit -framework Opencl

SRC = main.c \
		 init_mlx.c \
		 draw.c \
		 loop.c \
		 over_sampling_resize.c \
		 buddhabrot_color.c \
		 end_of_program.c \
		 event/event_key_off.c \
		 event/event_key_on.c \
		 event/event_mouse.c \
		 event/event_move_mouse.c \
		 cl/cl_draw.c \
		 cl/cl_check_err.c \
		 cl/cl_end_opencl.c \
		 cl/cl_init_opencl.c

SRC_DIR = srcs/

CC = gcc 

MODE = 

INC = includes/

INC_FILES = includes/fractol.h \
			includes/mlx.h

OBJET = $(SRC:.c=.o)

OBJ_DIR = objs/

.PHONY: all, clean, fclean, re, $(NAME), lft, start, end


all: $(OBJ_DIR) lib $(NAME)

p: make_preci all

make_preci:
	$(eval MODE := -D MODE_PRECI)
	@echo $(MODE)

gp: make_gpupreci all

make_gpupreci:
	$(eval MODE := -D MODE_GPU -D MODE_PRECI)
	@echo $(MODE)

g: make_gpu all

make_gpu :
	$(eval MODE := -D MODE_GPU)
	@echo $(MODE)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJET)) $(INC_FILES)
	@$(CC) $(MODE) -I$(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LIB) -lft -lmlx -lmlxji  $(FRAMEWORK) -o $(NAME)
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"
	@echo "$(MODE)"

$(OBJ_DIR) :
	@mkdir $(DIR_LIB)
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/cl
	@mkdir $(OBJ_DIR)/event

start:
	@echo "\033[4m\033[33mCreation de $(NAME)   ...\033[0m"

end:
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	@echo "\033[34m$^ \033[0m-> \033[1m\033[37m$@\033[0m"
	@($(CC) $(MODE) $(FLAGS)  -I./$(INC) -c -o $@ $<)

lib:
	@(cd $(DIR_LFT) && $(MAKE))
	@(cd $(DIR_MLXJI) && $(MAKE))
	@(cd $(DIR_MLX) && $(MAKE))
	@(cp $(DIR_MLXJI)libmlxji.a ./all_lib/)
	@(cp $(DIR_LFT)libft.a ./all_lib/)
	@(cp $(DIR_MLX)libmlx.a ./all_lib/)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@(cd $(DIR_LFT) && make clean)
	@(cd $(DIR_MLXJI) && make clean)
	@(cd $(DIR_MLX) && make clean)

fclean: clean
	@/bin/rm -f $(NAME)
	@(rm -rf $(DIR_LIB))
	@(cd $(DIR_LFT) && make fclean)
	@(cd $(DIR_MLXJI) && make fclean)

re: fclean all

rep : fclean p

reg : fclean g

regp : fclean gp
