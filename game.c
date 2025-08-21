#include "minilibx/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define GRE 0x0000FF00
#define RED 0x00FF0000
#define BLU 0x000000FF
#define ESC 65307

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
    for (int y = 0; y <= height; y++)
        mlx_pixel_put(mlx, win, x, y, RED);
}

void drawLineHorizontal(void *mlx, void *win, int y, int width)
{
    for (int x = 0; x <= width; x++)
        mlx_pixel_put(mlx, win, x, y, RED);
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 600, 600, "10x10 Grid");

    int blockSize = 50;
    int gridSize = blockSize * 10; // 500 pixels total

    // Draw vertical lines
    for (int col = 0; col <= 10; col++) {
        drawLineVertical(mlx, win, col * blockSize, gridSize);
    }

    // Draw horizontal lines
    for (int row = 0; row <= 10; row++) {
        drawLineHorizontal(mlx, win, row * blockSize, gridSize);
    }
    mlx_key_hook(win, handle_keypress, NULL);
    mlx_loop(mlx);
    return 0;
}



// void drawCircle(void *mlx, void *win, int xc, int yc, int x, int y)
// {
//     mlx_pixel_put(mlx, win, xc-x, yc+y, GRE);
//     mlx_pixel_put(mlx, win, xc+x, yc+y, GRE);
//     mlx_pixel_put(mlx, win, xc+x, yc-y, GRE);
//     mlx_pixel_put(mlx, win, xc-x, yc-y, GRE);
//     mlx_pixel_put(mlx, win, xc+y, yc+x, GRE);
//     mlx_pixel_put(mlx, win, xc-y, yc+x, GRE);
//     mlx_pixel_put(mlx, win, xc+y, yc-x, GRE);
//     mlx_pixel_put(mlx, win, xc-y, yc-x, GRE);
// }

// void circleBres(void *mlx, void *win, int xc, int yc, int r)
// {
//     int x = 0, y = r;
//     int d = 3 - 2 * r;

//     drawCircle(mlx, win, xc, yc, x, y);
//     while (y >= x)
//     {
//         if (d > 0)
//         {
//             y--; 
//             d = d + 4 * (x - y) + 10;
//         }
//         else
//             d = d + 4 * x + 6;
//         x++;
//         drawCircle(mlx, win, xc, yc, x, y);
//         usleep(30000);
//     }
// }

// int main ()
// {
//     void *mlx;
//     void *win;
//     int a;

//     mlx = mlx_init();
//     win = mlx_new_window(mlx, 1200, 1000, "game");
//     circleBres(mlx, win, 500, 500,300);    
//     // int b = 0;
//     // while (b < 100)
//     // {
//     //     printf("1\n");
//     //     a = 0;
//     //     while (a < 100)
//     //     {
//     //         printf("2\n");
//     //         mlx_pixel_put(mlx, win, a, b, 0x0000FF00); 
//     //         a++;
//     //     }
//     //     mlx_pixel_put(mlx, win, a, b, 0x0000FF00); 
//     //     b++;
//     // }
//     // a = b;
//     mlx_loop(mlx);
// }