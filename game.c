#include "game.h"

int	handle_keypress(int keycode)
{
	if (keycode == ESC)
	{
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void drawLineVertical(void *mlx, void *win, int x, int height)
{
    int y;

    y = 0;
    while (y <= height)
    {
        mlx_pixel_put(mlx, win, x, y, RED);
        y++;
    }
}

void drawLineHorizontal(void *mlx, void *win, int y, int width)
{
    int x;
    
    x = 0;
    while (x <= width)
    {
        mlx_pixel_put(mlx, win, x, y, RED);
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
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
int main()
{
	t_mlx mlx;

	int blockSize = 50;
	int gridSize = blockSize * 14;

	mlx_ini(&mlx);
	int col = 0;
	while (col <= 14)
	{
		int row = 0;
		while (row <= 14) 
		{
			drawLineHorizontal(mlx.mlx, mlx.win, row * blockSize, gridSize);
			row++;
		}
		drawLineVertical(mlx.mlx, mlx.win, col * blockSize, gridSize);
		col++;
	}
	circleBres(mlx.mlx, mlx.win, 350, 350, 10);
	for (int i = 0; i < 700; i++)
	{
		int j = i;
		mlx_pixel_put(mlx.mlx, mlx.win, i+1, j, BLU);
		j = i + 1;
		mlx_pixel_put(mlx.mlx, mlx.win, i+1, j + 1, BLU);
	}
	int i = 0;
	for (int j = 700; j > 0; j--)
	{
		mlx_pixel_put(mlx.mlx, mlx.win, i, j, GRE); 
		i++;
		mlx_pixel_put(mlx.mlx, mlx.win, i, j - 1, GRE);
		printf("here %d\n", i);
	}
	int x = 89;
	int y = 89;
	circleBres(mlx.mlx, mlx.win, 350, 350, 100);
/*
	circleBres(mlx, win, 350, 350, 150);
	circleBres(mlx, win, 350, 350, 200);
	circleBres(mlx, win, 350, 350, 200);
	circleBres(mlx, win, 350, 350, 250);
	circleBres(mlx, win, 350, 350, 300);
	circleBres(mlx, win, 350, 350, 350);
*/

	mlx_key_hook(mlx.win, handle_keypress, NULL);
	mlx_loop(mlx.mlx);

}

