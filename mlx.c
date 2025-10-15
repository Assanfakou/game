/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:14:39 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/10 00:07:50fakou           ###   ########.fr       */
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

t_cub cub_init(t_game *data)
{
	t_cub cub;
	t_render render;
	t_image image;
	t_image map_img;

	render.mlx = mlx_init();
	render.win = mlx_new_window(render.mlx, data->map_width * TILE, data->map_height * TILE, "game");
	image = new_image(render, data->map_width * TILE, data->map_height * TILE);
	map_img = new_image(render, data->map_width * TILEIM, data->map_height * TILEIM);
	cub.render = render;
	cub.image = image;
	cub.map_img = map_img;
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
