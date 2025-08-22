build:
	gcc *.c -Lminilibx -lmlx -lXext -lX11 -lm -o game
run:
	./game
clean:
	rm game