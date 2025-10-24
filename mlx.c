/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:04:17 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/24 18:50:20 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_image new_image(t_render render, int width, int height)
{
	t_image new_image;

	new_image.width = width;
	new_image.height = height;
	new_image.buff = mlx_new_image(render.mlx, width, height);
	new_image.addr = mlx_get_data_addr(new_image.buff, &new_image.bpp,
		&new_image.line_length, &new_image.endian);
	return (new_image);
}
t_textures get_texture_data(t_game *data, t_render *mlx)
{
	t_textures textures;
	t_image north;
	t_image east;
	t_image west;
	t_image south;

	// (void) data;
	// printf("name : %s\n", file);
	north.buff = mlx_xpm_file_to_image(mlx->mlx, data->north_texture, &north.width, &north.height);
	north.addr = mlx_get_data_addr(north.buff, &north.bpp, &north.line_length, &north.endian);

	east.buff = mlx_xpm_file_to_image(mlx->mlx, data->east_texture, &east.width, &east.height);
	east.addr = mlx_get_data_addr(east.buff, &east.bpp, &east.line_length, &east.endian);

	west.buff = mlx_xpm_file_to_image(mlx->mlx, data->west_texture, &west.width, &west.height);
	west.addr = mlx_get_data_addr(west.buff, &west.bpp, &west.line_length, &east.endian);

	south.buff = mlx_xpm_file_to_image(mlx->mlx, data->south_texture, &south.width, &south.height);
	south.addr = mlx_get_data_addr(south.buff, &south.bpp, &south.line_length, &south.endian);

	textures.north = north;
	textures.east = east;
	textures.west = west;
	textures.south = south;
	return (textures);
}
t_cub cub_init(t_game *data)
{
	t_cub cub;
	t_render render;
	t_image image;
	t_image map_img;
	// t_image texture_test;
	t_textures tex;

	render.mlx = mlx_init();
	render.win = mlx_new_window(render.mlx, data->map_width * TILE, data->map_height * TILE, "game");
	image = new_image(render, data->map_width * TILE, data->map_height * TILE);
	map_img = new_image(render, data->map_width * TILEIM, data->map_height * TILEIM);
	// texture_test = get_texture_data(data->north_texture, &render); 
	
	tex = get_texture_data(data, &render);
	cub.tex = tex;
	
	cub.render = render;
	cub.image = image;
	cub.map_img = map_img;
	// printf("address test %p\n", texture_test.addr);
	// cub.texture_test = texture_test;
	return (cub);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height) 
		return;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
