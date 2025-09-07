#include "game.h"


void drawLineVertical(t_mlx *mlx, int x, int height)
{
	int y;

	y = 0;
	while (y <= height)
	{
		my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x, y, RED);
		y++;
	}
}

void drawLineHorizontal(t_mlx *mlx, int y, int width)
{
	int x;

	x = 0;
	while (x <= width)
	{
		my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x, y, RED);
		x++;
	}
}

void draw_squar(t_mlx *mlx, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE)
	{
		j = 0;	
		while (j < TILE)
		{
			my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x * TILE + i, y * TILE + j, color);
			j++;
		}
		i++; 
	}
}

void draw_player(t_mlx *mlx, t_player *player)
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
				my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp,
						(int)player->x + i, (int)player->y + j, BLU);
			j++;
		}
		i++;
	}
}

void draw_grids(t_mlx *mlx)
{
	int gridSize = TILE * 14;
	int row;
	int col = 0;

	while (col <= 14)
	{
		row = 0;
		while (row <= 14)
		{
			drawLineHorizontal(mlx, row * TILE, gridSize);
			row++;
		}
		drawLineVertical(mlx, col * TILE, gridSize);
		col++;
	}
}
