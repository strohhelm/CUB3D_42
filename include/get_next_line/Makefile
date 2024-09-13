NAME := libget_next_line.a
CC := cc
CFLAGS ?= -Wall -Wextra -Werror

CFILES := 	get_next_line.c\
			get_next_line_utils.c

OBJFILES := obj/get_next_line.o\
			obj/get_next_line_utils.o

$(NAME): $(OBJFILES)
	@ar -rcs $@ $^


obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $^ -o $@ -g

all: $(NAME)
	
clean:
	@rm -rf obj

fclean:
	@rm -rf $(NAME) obj


re: fclean all

.PHONY: all clean fclean re t 
