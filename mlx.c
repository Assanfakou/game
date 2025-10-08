/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assankou <assankou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:14:39 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/08 17:36:20 by assankou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
int hight;
int width;
t_image new_image(t_render render, int width, int height)
{
	t_image new_image;

	new_image.width = width;
	new_image.height = height;
	new_image.buff = mlx_new_image(render.mlx, width, height);
	new_image.addr = mlx_get_data_addr(new_image.buff, &new_image.bpp, &new_image.line_length, &new_image.endian);
	return (new_image);
}

t_cub cub_init(t_game *data)
{
	t_cub cub;
	t_render render;
	t_image image;
	t_image map_img;

	render.mlx = mlx_init();
	hight = data->map_height * TILE;
	width = data->map_width * TILE;
	render.win = mlx_new_window(render.mlx, WIDTH, HEIGHT, "game");
	image = new_image(render, WIDTH, HEIGHT);
	map_img = new_image(render, data->map_width * TILEIM, data->map_height * TILEIM);
	printf("hight %d && width %d\n", data->map_height * TILEIM, data->map_width * TILEIM);
	cub.render = render;
	cub.image = image;
	printf("image adddress: %p\n", &cub.image);
	cub.map_img = map_img;
	return (cub);
}

void my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color)
{
	char *dst;

	if (x < -2 || y < 0 || x >= WIDTH || y >= HEIGHT) 
		return;
	dst = addr + (y * line_length + x * (bpp / 8));
	*(unsigned int*)dst = color;
}
