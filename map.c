/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:14:31 by hfakou            #+#    #+#             */
/*   Updated: 2025/11/01 20:19:36 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	draw_line_vertical(t_image *img, int x, int height)
{
	int	y;

	y = 0;
	while (y <= height)
	{
		my_mlx_pixel_put(img, x, y, 0xFFD700);
		y++;
	}
}

void	draw_line_horizontal(t_image *image, int y, int width)
{
	int	x;

	x = 0;
	while (x <= width)
	{
		my_mlx_pixel_put(image, x, y, RED);
		x++;
	}
}

void	draw_squar(t_image *image, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILEIM)
	{
		j = 0;
		while (j < TILEIM)
		{
			my_mlx_pixel_put(image, x * TILEIM + i, y * TILEIM + j, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_image *image, t_player *player)
{
	int	raduis;
	int	i;
	int	j;

	raduis = 4;
	i = -raduis;
	while (i <= raduis)
	{
		j = -raduis;
		while (j <= raduis)
		{
			if (i * i + j * j <= raduis * raduis)
				my_mlx_pixel_put(image, (player->vec_p->x / TILE) * TILEIM + i,
					player->vec_p->y / TILE * TILEIM + j, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_grids(t_cub *game)
{
	int	row;
	int	col;

	col = 0;
	while (col <= game->data->map_width)
	{
		row = 0;
		while (row <= game->data->map_height)
		{
			draw_line_horizontal(&game->map_img, row * TILEIM,
				game->data->map_width * TILEIM);
			row++;
		}
		draw_line_vertical(&game->map_img, col * TILEIM, game->data->map_height
			* TILEIM);
		col++;
	}
}
