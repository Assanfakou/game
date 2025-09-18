/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:14:31 by hfakou            #+#    #+#             */
/*   Updated: 2025/09/19 00:28:26 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void drawLineVertical(t_image *img, int x, int height)
{
	int y;

	y = 0;
	while (y <= height)
	{
		my_mlx_pixel_put(img->addr, img->line_length, img->bpp, x, y, RED);
		y++;
	}
}

void drawLineHorizontal(t_image *image, int y, int width)
{
	int x;

	x = 0;
	while (x <= width)
	{
		my_mlx_pixel_put(image->addr, image->line_length, image->bpp, x, y, RED);
		x++;
	}
}

void draw_squar(t_image *image, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILEIM)
	{
		j = 0;	
		while (j < TILEIM)
		{
			my_mlx_pixel_put(image->addr, image->line_length, image->bpp, x * TILEIM + i, y * TILEIM + j, color);
			j++;
		}
		i++; 
	}
}



void draw_player(t_image *image, t_player *player)
{
	int raduis;
	int i; 
	int j;
	
	raduis = 5;
	i = -raduis;
	while (i <= raduis)
	{
		j = -raduis;
		while (j <= raduis)
		{
			if (i*i + j*j <= raduis*raduis)
				my_mlx_pixel_put(image->addr, image->line_length, image->bpp, (player->x / TILE) * TILEIM + i, player->y / TILE * TILEIM + j, 0xFFFFFF);


			j++;
		}
		i++;
	}
}

void draw_grids(t_image *image)
{
	int gridSize = TILEIM;
	int row;
	int col = 0;

	while (col <= 14)
	{
		row = 0;
		while (row <= 14)
		{
			drawLineHorizontal(image, row * gridSize, WIDTHMAP);
			row++;
		}
		drawLineVertical(image, col * gridSize, HEIGHTMAP);
		col++;
	}
}
