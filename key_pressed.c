#include "game.h"

int	handle_keypress(int keycode)
{
	if (keycode == ESC)
	{
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int handle_keypres(int keycode, t_cub *game)
{
	t_player *player;
	double new_y;
	double new_x;
	int map_y;
	int map_x;

	player = game->player;
	if (keycode == UP)
	{
		new_y = player->y + player->dir_y * player->speed;
		new_x = player->x + player->dir_x * player->speed;
		map_y = (int)(new_y / TILE);
		map_x = (int)(new_x / TILE);
		if (game->map[map_y][map_x] != '1')
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (keycode == DOWN)
	{
		new_y = player->y - player->dir_y * player->speed;
		new_x = player->x - player->dir_x * player->speed;
		map_y = (int)(new_y / TILE);
		map_x = (int)(new_x / TILE);
		if (game->map[map_y][map_x] != '1')
		{
			player->x = new_x;
			player->y = new_y;
		}
	}
	if (keycode == LEFT)
	{
		player->angle -= 0.1;
		player->dir_x = cos(player->angle);
		player->dir_y = sin(player->angle);
	}
	if (keycode == RIGHT)
	{
		player->angle += 0.1;
		player->dir_x = cos(player->angle);
		player->dir_y = sin(player->angle);
	}
	return (0);
}
