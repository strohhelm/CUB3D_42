# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:32:41 by pstrohal          #+#    #+#              #
#    Updated: 2024/09/13 14:32:15 by timschmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m
SRC_PATH := src/
OBJ_PATH := obj/
INCLUDE_PATH := include/
		
SRC :=	main.c

OBJS := $(SRC:.c=.o)
NAME := cub3d
LIB := $(INCLUDE_PATH)libft
LIBG := $(INCLUDE_PATH)get_next_line
LIBFT := $(INCLUDE_PATH)libft/libft.a
MLX := $(INCLUDE_PATH)MLX42/build/libmlx42.a
FT_LIBS := $(LIBG)/libget_next_line.a $(LIBFT) $(MLX)

HEADER := cub.h -I ./include -I $(MLX_PATH)/include
ART = $(INCLUDE_PATH)art.txt
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

# $(LIBFT):
# 	@printf "$(GREEN)\n\nBuilding libraries\n\n$(RESET)"
# 	@make bonus -s -C $(LIB) & PID=$$!; \
# 	while kill -0 $$PID 2>/dev/null; do \
# 		printf "$(GREEN)█ $(RESET)"; \
# 		sleep 0.1; \
# 	done; \
# 	wait $$PID;
# 	@printf "$(GREEN)\n\nBuild complete.$(RESET)\n\n"

$(NAME): $(FT_LIBS) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(FT_LIBS) -o $(NAME) -ldl -lglfw -pthread -lm -g
	@make -s welcome 
	
$(FT_LIBS): 
	
	@make -s -C $(LIB)
	@make -s -C $(LIBG)
	@cd include && git clone https://github.com/codam-coding-college/MLX42.git
	@cd include/MLX42 && cmake -B build && cmake --build build -j4

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $^ -O0 -g

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
