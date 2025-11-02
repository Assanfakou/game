/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assankou <assankou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:12:12 by hfakou            #+#    #+#             */
/*   Updated: 2025/11/02 18:10:28 by assankou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	close_window(t_cub *game)
{
	mlx_clear_window(game->render.mlx, game->render.win);
	mlx_destroy_image(game->render.mlx, game->image.buff);
	mlx_destroy_image(game->render.mlx, game->map_img.buff);
	mlx_destroy_image(game->render.mlx, game->tex.east.buff);
	mlx_destroy_image(game->render.mlx, game->tex.north.buff);
	mlx_destroy_image(game->render.mlx, game->tex.west.buff);
	mlx_destroy_image(game->render.mlx, game->tex.south.buff);
	mlx_destroy_window(game->render.mlx, game->render.win);
	mlx_destroy_display(game->render.mlx);
	free(game->render.mlx);
	free_game_struct(game->data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	which_wall(t_dda *var, t_cub *game, bool flag)
{
	if (flag)
	{
		if (var->raydir.y > 0)
			game->dir = 'S';
		else
			game->dir = 'N';
	}
	else
	{
		if (var->raydir.x > 0)
			game->dir = 'E';
		else
			game->dir = 'W';
	}
}

void	check_screen(t_cub *game)
{
	int	screen_w;
	int	screen_h;

	mlx_get_screen_size(game->render.mlx, &screen_w, &screen_h);
	printf("map hight %d \n", game->data->map_height * TILE);
	printf("map width %d \n", game->data->map_width);
	printf("screen hight %d \n", screen_h);
	printf("screen width %d \n", screen_w);
	if (screen_h < game->data->map_height * TILE)
	{
		printf("height\n");
		close_window(game);
		exit(1);
	}
	if (screen_w < game->data->map_width * TILE)
	{
		printf("width\n");
		close_window(game);
		exit(1);
	}
}
