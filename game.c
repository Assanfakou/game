/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:04:17 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/16 20:31:10 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
dd
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
			x++;
		}
		y++;
	}
	
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
		my_mlx_pixel_put(img, x0, y0, color);
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
			printf("%c, ", map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}	
	printf("#############################################\n");
}
int rgb_to_int(int r, int g, int b)
{
	int collor;

	collor = (r << 16) | (g << 8) | b;
	return (collor);
}
void draw_floor_and_ceiling(t_image *image, t_game *game)
{
	int y = 0;
	while (y < image->height / 2)
	{
		int x = 0;
		while (x < image->width)
		{
			my_mlx_pixel_put(image, x, y, rgb_to_int(game->ceiling_color[0], game->ceiling_color[1], game->ceiling_color[2]));
			x++;
		}
		y++;
	}
	while (y < image->height)
	{
		int x = 0;
		while (x < image->width)
		{
			my_mlx_pixel_put(image, x, y, rgb_to_int(game->floor_color[0], game->floor_color[1], game->floor_color[2]));
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
	ft_bzero(game->image.addr, (size_t)game->image.line_length * game->data->map_height * TILE);
	ft_bzero(game->map_img.addr, (size_t)game->map_img.line_length * game->data->map_height * TILEIM);
	
	draw_grids(game);
	
	draw_player(&game->map_img, game->player);
	
	// printf("C %d F %d\n", game->data->ceiling_color[0], game->data->floor_color[0]);
	draw_map(game);
	draw_floor_and_ceiling(&game->image, game->data);
	cast_all_rays(game);
	printf("FPS: %d\n", (int)(1.0 / get_delta_time()));
	mlx_put_image_to_window(game->render.mlx, game->render.win, game->image.buff, 0, 0);
	mlx_put_image_to_window(game->render.mlx, game->render.win, game->map_img.buff, 0, 0);
	return 0;
}
void set_player(t_player *p, t_vector *p_v, t_vector *d, t_game data)
{
	p_v->x = data.player_x * TILE + TILE / 2;
	p_v->y = data.player_y * TILE + TILE / 2;
	p->vec_p = p_v;

	if (data.player_dir == 'N')
		p->angle = M_PI / 2 * 3;	
	else if (data.player_dir == 'S')
		p->angle = M_PI / 2;
	else if (data.player_dir == 'W')
		p->angle = M_PI;	
	else if (data.player_dir == 'E')
		p->angle = 0;	

	d->x = cos(p->angle);
	d->y = sin(p->angle);
	p->vec_d = d;
	p->speed = 10;
}
		
int main(int ac, char **av)
{
	t_cub cub;
	t_player player;
	t_game data;
	t_vector p_v;
	t_vector d;

	if (get_data(&data, ac, av))
		return 1;
	print_map(data.map);
	
	cub = cub_init(&data);

	set_player(&player, &p_v, &d, data);
	
	cub.player = &player;
	cub.data = &data;

	draw_map(&cub);
	print_map(cub.data->map);
	
	mlx_put_image_to_window(cub.render.mlx, cub.render.win, cub.image.buff, 0, 0);
	mlx_put_image_to_window(cub.render.mlx, cub.render.win, cub.map_img.buff, 0, 0);
	mlx_hook(cub.render.win, 2, 1L<<0, handle_keypres, &cub);
	mlx_loop_hook(cub.render.mlx, render, &cub);
	mlx_key_hook(cub.render.win, handle_keypress, NULL);
	mlx_loop(cub.render.mlx);
}

