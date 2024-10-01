# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:32:41 by pstrohal          #+#    #+#              #
#    Updated: 2024/10/01 16:10:27 by timschmi         ###   ########.fr        #
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
LIBFT := $(INCLUDE_PATH)libft/libft.a
MLX := $(INCLUDE_PATH)MLX42/build/libmlx42.a
FT_LIBS := $(LIBG)/libget_next_line.a $(LIBFT) $(MLX)

HEADER := cub.h -I ./include -I $(MLX_PATH)/include
ART = $(INCLUDE_PATH)art.txt
CC = cc
CFLAGS = -fsanitize=address #-Wall -Wextra -Werror-Ofast
DEPFLAGS= -MMD -MP
all: $(NAME)

$(NAME): $(FT_LIBS) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FT_LIBS) -o $(NAME) -ldl -lglfw -pthread -lm -g
	@make -s welcome 
	
$(FT_LIBS): 
	
	@make -s -C $(LIB)
	@make -s -C $(LIBG)
	# @cd include && git clone https://github.com/codam-coding-college/MLX42.git
	# @cd include/MLX42 && cmake -B build && cmake --build build -j4

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -o $@ -c $^ -g

clean:
	@make clean -s -C $(LIB)
	@make clean -s -C $(LIBG)
	@rm -rf obj

fclean: clean
	@make fclean -s -C $(LIB)
	@make fclean -s -C $(LIBG)
	@rm -rf $(OBJS)

welcome:
	@cat $(ART)

re: fclean all

.PHONY: all clean fclean re print welcome ft
