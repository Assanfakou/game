#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <math.h>

#define WIDTH 1100
#define HEIGHT 1000
#define TILE 50

#define GRE 0x0000FF00
#define RED 0x00FF0000
#define BLU 0x000000FF
#define ESC 65307


#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97

typedef struct s_player
{
	double x;
	double y;
	double dir_x;
	double dir_y;
	double angle;
	double speed;
}	t_player;

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

typedef struct s_cub
{
	char **map;
	t_mlx *mlx;
	t_player *player;

}	t_cub;

void my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color);
