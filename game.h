#include "minilibx/mlx.h"
#include "libft/libft.h"

#define WIDTH 700
#define HEIGHT 700
#define TILE 50

#define GRE 0x0000FF00
#define RED 0x00FF0000
#define BLU 0x000000FF
#define ESC 65307



typedef struct s_player
{
	double x;
	double y;
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
