#include "minilibx/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 1200
#define HEIGHT 1000

#define GRE 0x0000FF00
#define RED 0x00FF0000
#define BLU 0x000000FF
#define ESC 65307



typedef struct s_mlx
{
	void *win;
	void *mlx;
	void *addr;
	void *img;
	int bpp;
	int line_length;
	int endian;
}	t_mlx;
 	
