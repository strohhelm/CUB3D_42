# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:32:41 by pstrohal          #+#    #+#              #
#    Updated: 2024/10/24 17:12:29 by pstrohal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
BNAME = bcub3d
SRC_PATH = src
OBJ_PATH = obj
BON_PATH = bonus
BON_OBJ_PATH = bonus_obj
INCLUDE_PATH = include
CC = cc
ART := $(INCLUDE_PATH)/art.txt

FILES =	main.c \
			collision.c \
			error.c \
			movement.c \
			raycaster.c \
			cast_textures.c \
			read_input.c \
			read_input_utils.c \
			read_map.c \
			read_map_utils.c \
			read_settings.c \
			utils.c \
			render.c \
			free.c 

BFILES = 	main_bonus.c \
			cast_textures_bonus.c \
			collision_bonus.c \
			doors_bonus.c \
			draw_line_bonus.c \
			error_bonus.c \
			minimap_bonus.c \
			movement_bonus.c \
			raycaster_bonus.c \
			read_input_utils_bonus.c \
			read_input_bonus.c \
			read_map_utils_bonus.c \
			read_map_bonus.c \
			read_settings_bonus.c \
			utils_bonus.c \
			player_bonus.c \
			grid_bonus.c \
			textures_bonus.c \
			render_bonus.c

SRC := $(addprefix $(SRC_PATH)/, $(FILES))
OBJS := $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

BON := $(addprefix $(BON_PATH)/, $(BFILES))
BOBJ := $(patsubst $(BON_PATH)/%.c, $(BON_OBJ_PATH)/%.o, $(BON))

LIB := $(INCLUDE_PATH)/libft
LIBFT := $(LIB)/libft.a
LIBFT_FLAGS:= -L$(LIB) -lft

LIBG := $(INCLUDE_PATH)/get_next_line
LIBGET := $(LIBG)/libget_next_line.a
GET_FLAGS := -L$(LIBG) -lget_next_line

MLX := $(INCLUDE_PATH)/MLX42/build
LIBMLX := $(MLX)/libmlx42.a
MLXFLAGS = -L$(MLX) -lmlx42 -lglfw -ldl -pthread


CFLAGS = -Wall -Wextra -fsanitize=address -g -O0
LIBFLAGS := $(MLXFLAGS) $(GET_FLAGS) $(LIBFT_FLAGS) -lm

all: $(NAME)

bonus: $(BNAME)

$(NAME):  $(LIBFT) $(LIBGET) $(LIBMLX) $(OBJS)
	@$(CC) -o $@ $(OBJS) $(LIBFLAGS) $(CFLAGS)
	@make -s welcome
	
$(BNAME): $(LIBFT) $(LIBGET) $(LIBMLX) $(BOBJ)
	@$(CC) -o $@ $(BOBJ) $(LIBFLAGS) $(CFLAGS)
	@cat include/artbonus.txt

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus_obj/%.o: bonus/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -s -C $(LIB)

$(LIBGET):
	@make -s -C $(LIBG)

$(LIBMLX):
	@git submodule update --init --recursive >/dev/null 2>&1
	@cd include/MLX42 && cmake -B build >/dev/null 2>&1 && cmake --build build -j4 >/dev/null 2>&1

clean:
	@make clean -s -C $(LIB)
	@make clean -s -C $(LIBG)
	@rm -rf obj
	@rm -rf bonus_obj

deinit:
	@rm -rf include/MLX42 2>&1;

fclean: clean
	@make fclean -s -C $(LIB)
	@make fclean -s -C $(LIBG)
	@rm -rf $(NAME)
	@rm -rf $(BNAME)
	
welcome:
	@cat $(ART)

rb: fclean bonus

re: fclean all

.PHONY: all clean fclean bonus re welcome
