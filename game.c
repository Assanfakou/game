/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:04:17 by hfakou            #+#    #+#             */
/*   Updated: 2025/11/01 22:17:52 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


void	draw_map(t_cub *game)
{
	int		x;
	int		y;
	char	**map;

	y = 0;
	map = game->data->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_squar(&game->map_img, x, y, 0xFFD700);
			x++;
		}
		y++;
	}
}

void	draw_floor_and_ceiling(t_image *image, int *ceiling, int *floor)
{
	int	y;
	int	x;

	y = 0;
	while (y < image->height / 2)
	{
		x = 0;
		while (x < image->width)
		{
			my_mlx_pixel_put(image, x, y, rgb_to_int(ceiling));
			x++;
		}
		y++;
	}
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			my_mlx_pixel_put(image, x, y, rgb_to_int(floor));
			x++;
		}
		y++;
	}
}

int	render(t_cub *game)
{
	ft_bzero(game->image.addr, (size_t)game->image.line_length
		* game->data->map_height * TILE);
	ft_bzero(game->map_img.addr, (size_t)game->map_img.line_length
		* game->data->map_height * TILEIM);
	draw_grids(game);
	draw_player(&game->map_img, game->player);
	draw_map(game);
	draw_floor_and_ceiling(&game->image, game->data->ceiling_color,
		game->data->floor_color);
	cast_all_rays(game);
	printf("FPS: %d\n", (int)(1.0 / get_delta_time()));
	mlx_put_image_to_window(game->render.mlx, game->render.win,
		game->image.buff, 0, 0);
	mlx_put_image_to_window(game->render.mlx, game->render.win,
		game->map_img.buff, 0, 0);
	return (0);
}

void	set_player(t_player *p, t_vector *p_v, t_vector *d, t_game data)
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

int	main(int ac, char **av)
{
	t_cub		cub;
	t_player	player;
	t_game		data;
	t_vector	p_v;
	t_vector	d;

	if (get_data(&data, ac, av))
		return (1);
	cub = cub_init(&data);
	set_player(&player, &p_v, &d, data);
	cub.player = &player;
	cub.data = &data;
	cub.fov = M_PI / 3;
	draw_map(&cub);
	int    screen_w;
	int    screen_h;

	mlx_get_screen_size(cub.render.mlx, &screen_w, &screen_h);
	printf("map hight %d \n", cub.data->map_height);
	if (screen_h < cub.data->map_height * TILE)
	{
		printf("height\n");
		exit(1);
	}
	if (screen_w < cub.data->map_width * TILE)
	{
		printf("width\n");
		exit(1);
	}
	mlx_put_image_to_window(cub.render.mlx, cub.render.win, cub.image.buff, 0,
		0);
	mlx_put_image_to_window(cub.render.mlx, cub.render.win, cub.map_img.buff, 0,
		0);
	mlx_hook(cub.render.win, 2, 1L << 0, handle_keypress, &cub);
	mlx_loop_hook(cub.render.mlx, render, &cub);
	mlx_hook(cub.render.win, 17, 0, close_window, &cub);
	mlx_loop(cub.render.mlx);
}
