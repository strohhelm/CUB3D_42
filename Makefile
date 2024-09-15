# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:32:41 by pstrohal          #+#    #+#              #
#    Updated: 2024/09/14 18:48:29 by timschmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH := src/
OBJ_PATH := obj/
INCLUDE_PATH := include/
		
SRC :=	main.c draw_line.c raycaster.c

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
CFLAGS =  -fsanitize=address # -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(FT_LIBS) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FT_LIBS) -o $(NAME) -ldl -lglfw -pthread -lm 
	@make -s welcome 
	
$(FT_LIBS): 
	
	@make -s -C $(LIB)
	@make -s -C $(LIBG)
	@cd include && git clone https://github.com/codam-coding-college/MLX42.git
	@cd include/MLX42 && cmake -B build && cmake --build build -j4

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make clean -s -C $(LIB)
	@make clean -s -C $(LIBG)
	@rm -rf %.o

fclean: clean
	@make fclean -s -C $(LIB)
	@make fclean -s -C $(LIBG)
	@rm -rf $(OBJS)

welcome:
	@cat $(ART)

re: fclean all

.PHONY: all clean fclean re print welcome ft
