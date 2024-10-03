# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:32:41 by pstrohal          #+#    #+#              #
#    Updated: 2024/10/03 16:14:23 by timschmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC_PATH = src
OBJ_PATH = obj
INCLUDE_PATH = include
# DEP_PATH := $(OBJ_PATH)/.dep
CC = cc

FILES =	main.c \
			collision.c \
			draw_line.c \
			error.c \
			movement.c \
			raycaster.c \
			cast_textures.c \
			read_input.c \
			read_input_utils.c \
			read_map.c \
			read_settings.c \
			utils.c \
			player.c \
			grid.c \
			render.c

SRC := $(addprefix $(SRC_PATH)/, $(FILES))
OBJS := $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o,$(SRC))
# DFLS := $(OBJS:.o=.d)
ART := $(INCLUDE_PATH)/art.txt


LIB := $(INCLUDE_PATH)/libft
LIBFT := $(LIB)/libft.a
LIBFT_FLAGS:= -L$(LIB) -lft

LIBG := $(INCLUDE_PATH)/get_next_line
LIBGET := $(LIBG)/libget_next_line.a
GET_FLAGS := -L$(LIBG) -lget_next_line

MLX := $(INCLUDE_PATH)/MLX42/build
LIBMLX := $(MLX)/libmlx42.a
MLXFLAGS = -L$(MLX) -lmlx42 -lglfw


CFLAGS = -Wall -Wextra -Werror -Ofast
# DEPFLAGS = -MMD -MP
LIBFLAGS := $(MLXFLAGS) $(GET_FLAGS) $(LIBFT_FLAGS) -lm

ifeq ($(DEBUG), 1)
		CFLAGS += -fsanitize=address -g -O0
endif

# -include $(DFLS)

all: $(NAME)

$(NAME):  $(LIBFT) $(LIBGET) $(LIBMLX) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LIBFLAGS) 
	@make -s welcome
	
$(LIBFT):
	@make -s -C $(LIB)
	
$(LIBGET):
	@make -s -C $(LIBG)

$(LIBMLX):
	@git submodule update --init --recursive
	@cd include/MLX42 && cmake -B build --quiet && cmake --build build -j4 --quiet

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

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

.PHONY: all clean fclean re welcome
