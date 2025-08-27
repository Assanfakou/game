#include "game.h"

int	handle_keypress(int keycode)
{
	if (keycode == ESC)
	{
		exit(EXIT_SUCCESS);
	}
	return (0);
}

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

void drawCircle(void *mlx, void *win, int xc, int yc, int x, int y)
{
    mlx_pixel_put(mlx, win, xc-x, yc+y, GRE);
    mlx_pixel_put(mlx, win, xc+x, yc-y, GRE);
    mlx_pixel_put(mlx, win, xc-x, yc-y, GRE);
    mlx_pixel_put(mlx, win, xc+y, yc+x, GRE);
    mlx_pixel_put(mlx, win, xc-y, yc+x, GRE);
    mlx_pixel_put(mlx, win, xc+y, yc-x, GRE);
    mlx_pixel_put(mlx, win, xc-y, yc-x, GRE);
    mlx_pixel_put(mlx, win, xc+x, yc+y, GRE);
}

void circleBres(void *mlx, void *win, int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    drawCircle(mlx, win, xc, yc, x, y);
    while (y >= x)
    {
        if (d > 0)
        {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        x++;
        drawCircle(mlx, win, xc, yc, x, y);
        usleep(10);
    }
}

void mlx_ini(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "14x14 Grid");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr= mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_length, &mlx->endian);
}

void my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0) 
	return;  // avoid invalid coords
    dst = addr + (y * line_length + x * (bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_squar(t_mlx *mlx, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE)
	{
		j = y;	
		while (j < TILE)
		{
			my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, i * TILE, j * TILE, color);
			j++;
		}
		i++; 
	}
}

void draw_region(char *addr, int line_length, int bpp, int x_start, int x_end, int y_start, int y_end, int color)
{
    for (int y = y_start; y <= y_end; y++)
    {
        for (int x = x_start; x <= x_end; x++)
        {
            my_mlx_pixel_put(addr, line_length, bpp, x, y, color);
        }
    }
}

void draw_grids(t_mlx *mlx)
{
	
	int blockSize = 50;
	int gridSize = blockSize * 14;
	int row;
	int col = 0;

	while (col <= 14)
	{
		row = 0;
		while (row <= 14)
		{
			drawLineHorizontal(mlx, row * blockSize, gridSize);
			row++;
		}
		drawLineVertical(mlx, col * blockSize, gridSize);
		col++;
	}
}
int main()
{
	t_mlx mlx;
	t_cub cub;

	char map[14][14] = {
	{"P1111111111111"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"10000000000001"},
	{"11111111111111"},
	};
	mlx_ini(&mlx);
	draw_grids(&mlx);
	draw_region(mlx.addr, mlx.line_length, mlx.bpp, 100, 200, 200, 300, RED); 
	circleBres(mlx.mlx, mlx.win, 350, 350, 10);
	circleBres(mlx.mlx, mlx.win, 350, 350, 100);

	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_key_hook(mlx.win, handle_keypress, NULL);
	mlx_loop(mlx.mlx);

}

