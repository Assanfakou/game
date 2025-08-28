build:
	make -C libft
	gcc *.c -Lminilibx -lmlx -lXext -lX11 -lm libft/libft.a -o game && ./game
clean:
	rm game
