#include "minilibx/mlx.h"
#include <stdio.h>
#include <unistd.h>

#define GR 0x0000FF00
#define RE 0x00FF0000
#define BL 0x000000FF

int main ()
{
    void *mlx;
    void *win;
    int a;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 1200, 1000, "game");
    int b = 0;
    while (b < 100)
    {
        printf("1\n");
        a = 0;
        while (a < 100)
        {
            printf("2\n");
            mlx_pixel_put(mlx, win, a, b, 0x0000FF00); 
            a++;
        }
        mlx_pixel_put(mlx, win, a, b, 0x0000FF00); 
        b++;
    }
    
    mlx_loop(mlx);
}