# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:32:41 by pstrohal          #+#    #+#              #
#    Updated: 2024/10/02 18:11:44 by pstrohal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH := src/
OBJ_PATH := obj/
INCLUDE_PATH := include/
		
FILES :=	main.c \
			collision.c \
			draw_line.c \
			error.c \
			movement.c \
			raycaster.c \
			read_input.c \
			read_input_utils.c \
			read_map.c \
			read_settings.c \
			utils.c \
			player.c \
			grid.c \
			render.c
			

SRC := $(addprefix src/,$(FILES))
OBJS := $(patsubst src/%.c, obj/%.o,$(SRC))
NAME := cub3d
LIB := $(INCLUDE_PATH)libft
LIBG := $(INCLUDE_PATH)get_next_line
LIBFT := $(LIB)/libft.a
LIBGET := $(LIBG)/libget_next_line.a
MLX := $(INCLUDE_PATH)MLX42/build/libmlx42.a
FT_LIBS := $(LIBFT) $(LIBGET) $(MLX)
HEADER := cub.h -I ./include -I $(MLX_PATH)/include
ART = $(INCLUDE_PATH)art.txt
CC = cc
CFLAGS =  -Wall -Wextra -Werror -Ofast #-fsanitize=address 
DEPFLAGS= -MMD -MP
all: $(NAME)

$(NAME): FT_LIBS $(OBJS)
	@$(CC) $(CFLAGS) $(DEPFLAGS) $(OBJS) $(FT_LIBS) -o $(NAME) -ldl -lglfw -pthread -lm -g
	@make -s welcome
	
FT_LIBS: $(LIBGET) $(LIBFT) $(MLX)

$(LIBFT) :
	@make -s -C $(LIB)
$(LIBGET):
	@make -s -C $(LIBG)
$(MLX):
	@git submodule update --init --recursive
	@cd include/MLX42 && cmake -B build --quiet && cmake --build build -j4 --quiet -O0

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -o $@ -c $^ -g -O0

clean:
	@make clean -s -C $(LIB)
	@make clean -s -C $(LIBG)
	@rm -rf obj

fclean: clean
	@make fclean -s -C $(LIB)
	@make fclean -s -C $(LIBG)
	@rm -rf $(NAME)

welcome:
	@cat $(ART)

re: fclean all

.PHONY: all clean fclean re print welcome ft
