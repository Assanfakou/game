/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assankou <assankou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:04:17 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/07 01:58:07 by assankou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void draw_map(t_cub *game)
{
	int x;
	int y;
	char **map;

	y = 0;
	map = game->data->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			 	draw_squar(&game->map_img, x, y, RED);
			if (map[y][x] == 'N')
			{
				// game->player->vec_p->x = x * TILE + TILE /2;
				// game->player->vec_p->y = y * TILE + TILE /2;
				// map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	printf("here3\n");
	
}

void	update_point(int *x0, int *y0, int *err, int dx, int dy, int sx, int sy)
{
	int	e2;

	e2 = *err * 2;
	if (e2 > -dy)
	{
		*err -= dy;
		*x0 += sx;
	}
	if (e2 < dx)
	{
		*err += dx;
		*y0 += sy;
	}
}

void	draw_line(t_image *img, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		my_mlx_pixel_put(img->addr, img->line_length, img->bpp, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		update_point(&x0, &y0, &err, dx, dy, sx, sy);
	}
}

void print_map(char **map)
{
	int y = 0;
	int x;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			printf("%c", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}	
	printf("#############################################\n");
}

void draw_floor_and_ceiling(t_image *image)
{
	int y = 0;
	while (y < HEIGHT / 2)
	{
		int x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(image->addr, image->line_length, image->bpp, x, y, GRE);
			x++;
		}
		y++;
	}

	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(image->addr, image->line_length, image->bpp, x, y, RED);
			x++;
		}
		y++;
	}
}

double get_delta_time(void)
{
	static struct timeval last_time = {0, 0};
	struct timeval current_time;
	double delta;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0 && last_time.tv_usec == 0)
		last_time = current_time;

	delta = (current_time.tv_sec - last_time.tv_sec) +
		(current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	last_time = current_time;
	return (delta);
}

int render(t_cub *game)
{
	ft_bzero(game->image.addr, (size_t)game->image.line_length * HEIGHT);
	ft_bzero(game->map_img.addr, (size_t)game->map_img.line_length * HEIGHTMAP);
	
	draw_grids(game);
	//colorize(&game->map_img, WIDTHMAP, HEIGHTMAP);
	
	draw_player(&game->map_img, game->player);
	
	draw_map(game);
	//draw_floor_and_ceiling(game->image);
	cast_all_rays(game);
	printf("debug here\n");
	//cast_all_map_rays(game);
	printf("FPS : %d\n", (int)(1.0 / get_delta_time()));
	mlx_put_image_to_window(game->render.mlx, game->render.win, game->image.buff, 0, 0);

	mlx_put_image_to_window(game->render.mlx, game->render.win, game->map_img.buff, 0, 0);
	return 0;
}

int main(int ac, char **av)
{
	t_cub cub;
	t_player player;
	t_game data;

	if (get_data(&data, ac, av))
		return 1;
	print_map(data.map);
	// printf("player pos x %d,y %d\n", data.player_x, data.player_y);
	
	cub = cub_init(&data);
	printf("player pos2 x (*%c)\n", data.map[0][0]);
	player.speed = 10;
	player.angle = 0;
	t_vector p;
	t_vector d;
	p.x = data.player_x * TILE + TILE / 2;
	p.y = data.player_y * TILE + TILE / 2;
	d.x = cos(player.angle);
	d.y = sin(player.angle);
	player.vec_d = &d;
	player.vec_p = &p;
	cub.player = &player;
	cub.data = &data;

	//draw_grids(&cub.map_img);
	draw_map(&cub);
	printf("here4\n");
	
	mlx_put_image_to_window(cub.render.mlx, cub.render.win, cub.image.buff, 0, 0);
	mlx_put_image_to_window(cub.render.mlx, cub.render.win, cub.map_img.buff, 0, 0);
	mlx_hook(cub.render.win, 2, 1L<<0, handle_keypres, &cub);
	mlx_loop_hook(cub.render.mlx, render, &cub);
	mlx_key_hook(cub.render.win, handle_keypress, NULL);
	mlx_loop(cub.render.mlx);
}

