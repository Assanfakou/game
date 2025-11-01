/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:04:17 by hfakou            #+#    #+#             */
/*   Updated: 2025/11/01 19:53:03 by hfakou           ###   ########.fr       */
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

t_image	new_image(t_render render, int width, int height)
{
	t_image	new_image;

	new_image.width = width;
	new_image.height = height;
	new_image.buff = mlx_new_image(render.mlx, width, height);
	new_image.addr = mlx_get_data_addr(new_image.buff, &new_image.bpp,
			&new_image.line_length, &new_image.endian);
	return (new_image);
}
void get_bufer_texture(t_image *image, t_render *mlx, char *texture)
{
	image->buff = mlx_xpm_file_to_image(mlx->mlx, texture, 
		&image->width, &image->height);
	image->addr = mlx_get_data_addr(image->buff, &image->bpp, 
		&image->line_length, &image->endian);
}
t_textures	get_texture_data(t_game *data, t_render *mlx)
{
	t_textures	textures;
	t_image		north;
	t_image		east;
	t_image		west;
	t_image		south;

	get_bufer_texture(&north, mlx, data->north_texture);
	get_bufer_texture(&east, mlx, data->east_texture);
	get_bufer_texture(&west, mlx, data->west_texture);
	get_bufer_texture(&south, mlx, data->south_texture);
	textures.north = north;
	textures.east = east;
	textures.west = west;
	textures.south = south;
	return (textures);
}

t_cub	cub_init(t_game *data)
{
	t_cub		cub;
	t_render	render;
	t_image		image;
	t_image		map_img;
	t_textures	tex;

	render.mlx = mlx_init();
	render.win = mlx_new_window(render.mlx, data->map_width * TILE,
			data->map_height * TILE, "game");
	image = new_image(render, data->map_width * TILE, data->map_height * TILE);
	map_img = new_image(render, data->map_width * TILEIM, data->map_height
			* TILEIM);
	tex = get_texture_data(data, &render);
	cub.tex = tex;
	cub.render = render;
	cub.image = image;
	cub.map_img = map_img;
	return (cub);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
