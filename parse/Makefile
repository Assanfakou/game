CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cub
SOURCES = main.c file_utilis.c game_utilis.c texture_file_ops.c texture_validation.c parsing_element.c map.c utilis.c color_parsing.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(NAME)

%.o: %.c parsing.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re