/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:04:17 by hfakou            #+#    #+#             */
/*   Updated: 2025/09/11 21:35:30 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void draw_map(t_cub *game)
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
				draw_squar(&game->image, x, y, RED);
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

void draw_line(t_image *image, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(image->addr, image->line_length, image->bpp, x0, y0, color);
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

void colorize(t_image *image, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			my_mlx_pixel_put(image->addr, image->line_length, image->bpp, i, j, RED);			
		}
	}
}

int render(t_cub *game)
{
	printf("adress %p\n", &game->image.addr);
	ft_bzero(&game->image.addr, (size_t)game->image.line_length * HEIGHT);
	printf("%sangle :%f%s, \n", COLORE, game->player->angle, RESET);
	//ft_bzero(&game->map_img.addr, (size_t)game->map_img.line_length * HEIGHTMAP);

	draw_grids(&game->image);
	colorize(&game->image, WIDTHMAP, HEIGHTMAP);
	draw_player(&game->image, game->player);
 	draw_map(game);
	//print_map(game);
	//draw_floor_and_ceiling(game->mlx);
	// cast_all_rays(game);
	printf("cos of angle :%f, \n", cos(game->player->angle));

/*
	mlx_put_image_to_window(&game->render.mlx, &game->render.win, game->map_img.buff, 0, 0);
*/
	mlx_put_image_to_window(&game->render.mlx, &game->render.win, game->image.buff, 0, 0);
	return 0;
}

int main()
{
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
	cub = cub_init(map);
	player.speed = 10;
	player.angle = 0;
	player.dir_x = cos(player.angle);
	player.dir_y = sin(player.angle);
	cub.player = &player;
	print_map(&cub);
	printf("win addr %p\n mlx addr %p\n", cub.render.win, cub.render.mlx);

	//draw_grids(&cub.image);
	draw_map(&cub);
	
	mlx_put_image_to_window(cub.render.mlx, cub.render.win, cub.image.buff, 0, 0);
//	mlx_put_image_to_window(cub.render.mlx, cub.render.win, cub.map_img.buff, 0, 0);
	mlx_hook(cub.render.win, 2, 1L<<0, handle_keypres, &cub);
	mlx_loop_hook(cub.render.mlx, render, &cub);
	//mlx_key_hook(cub.render.win, handle_keypress, NULL);
	mlx_loop(cub.render.mlx);
}

