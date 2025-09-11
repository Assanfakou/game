#include "game.h"

#define TILEIM 10 
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
	while (i < TILE)
	{
		j = 0;	
		while (j < TILE)
		{
			my_mlx_pixel_put(image->addr, image->line_length, image->bpp, x * TILE + i, y * TILE + j, color);
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

	raduis = 10;
	i = -raduis;
	while (i <= raduis)
	{
		j = -raduis;
		while (j <= raduis)
		{
			if (i*i + j*j <= raduis*raduis)
				my_mlx_pixel_put(image->addr, image->line_length, image->bpp,
						(int)player->x + i, (int)player->y + j, BLU);
			j++;
		}
		i++;
	}
}


void draw_grids(t_image *image)
{
	int gridSize = TILEIM * 14;
	int row;
	int col = 0;

	while (col <= 14)
	{
		row = 0;
		while (row <= 14)
		{
			drawLineHorizontal(image, row * TILEIM, 20);
			row++;
		}
		drawLineVertical(image, col * TILEIM, 20);
		col++;
	}
}
