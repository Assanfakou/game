#include "game.h"

void draw_map(t_cub *game, t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
/*
			if (game->map[y][x] == '0')
				draw_squar(mlx, x, y, RED);
*/
			if (game->map[y][x] == 'P')
			{
				game->player->x = x * TILE + TILE / 2;
				game->player->y = y * TILE + TILE / 2;
				game->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}

void draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x0, y0, color);
        if (x0 == x1 && y0 == y1)
		break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx;}
        if (e2 <  dx) { err += dx; y0 += sy; }
    }
}

void print_map(t_cub *game)
{
	int y = 0;
	int x;

	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			printf("%c, ", game->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}	
	printf("#############################################\n");
}

void draw_floor_and_ceiling(t_mlx *mlx)
{
	int y = 0;
	while (y < HEIGHT / 2)
	{
		int x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x, y, GRE);
			x++;
		}
		y++;
	}

	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x, y, RED);
			x++;
		}
		y++;
	}
}

int render(t_cub *game)
{
	ft_bzero(game->mlx->addr, (size_t)game->mlx->line_length * HEIGHT);
	//ft_bzero(game->map_image, (size_t)game->map_image->line_length * HEIGHT / 2);

	//draw_grids(game->map_image);
	//draw_player(game->map_image, game->player);
	//draw_map(game, game->map_image);
	//print_map(game);
	//draw_floor_and_ceiling(game->mlx);
	cast_all_rays(game);
//	draw_fov(game);
	printf("%sangle :%f%s, \n", COLORE, game->player->angle, RESET);
	printf("cos of angle :%f, \n", cos(game->player->angle));

	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->mlx->img, 0, 0);
	return 0;
}

int main()
{
	t_mlx mlx;
	t_mlx map_image;
	t_cub cub;
	t_player player;
	char *map[] = {
		strdup("11111111111111"),
		strdup("1P000010010001"),
		strdup("10100001000001"),
		strdup("10000000100001"),
		strdup("10100000000001"),
		strdup("10110010000001"),
		strdup("10000000000001"),
		strdup("10000000000001"),
		strdup("10000000000001"),
		strdup("10000000000001"),
		strdup("10000000000001"),
		strdup("10000000000001"),
		strdup("10000000000001"),
		strdup("11111111111111"),
		NULL
	};

	mlx_ini(&mlx, &map_image);
	cub.map = map;
	player.speed = 10;
	player.angle = 0;
	player.dir_x = cos(player.angle);
	player.dir_y = sin(player.angle);
	cub.player = &player;
	cub.mlx = &mlx;
	cub.map_image = &map_image;

	//draw_grids(&mlx);
	draw_map(&cub, &mlx);
	
//	mlx_put_image_to_window(mlx.mlx, mlx.win, map_image.img, 0, 0);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_hook(mlx.win, 2, 1L<<0, handle_keypres, &cub);
	mlx_loop_hook(mlx.mlx, render, &cub);
	mlx_key_hook(mlx.win, handle_keypress, NULL);
	mlx_loop(mlx.mlx);
}

