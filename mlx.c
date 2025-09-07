#include "game.h"

void mlx_ini(t_mlx *mlx, t_mlx *map_image)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "14x14 Grid");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_length, &mlx->endian);
	
	map_image->img = mlx_new_image(mlx->mlx, 100, 100);
	map_image->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_length, &mlx->endian);
	map_image->mlx = mlx->mlx;
	map_image->win = mlx->win; 
}

void my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color)
{
	char *dst;

	if (x < -2 || y < 0 || x >= WIDTH || y >= HEIGHT) 
		return;
	dst = addr + (y * line_length + x * (bpp / 8));
	*(unsigned int*)dst = color;
}
