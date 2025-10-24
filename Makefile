CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3
NAME = cub
MLX = -Lminilibx -lmlx -lXext -lX11 -lm -g -g3
INCLUDE = libft/libft.a
SOURCES = parse/main.c parse/file_utilis.c parse/game_utilis.c parse/texture_file_ops.c parse/texture_validation.c parse/parsing_element.c parse/map.c parse/utilis.c parse/color_parsing.c \
	game.c key_pressed.c map.c mlx.c ray_cast.c 
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(INCLUDE):
	make  -C libft
$(NAME): $(OBJECTS) $(INCLUDE)
	$(CC) $(OBJECTS) $(INCLUDE) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
