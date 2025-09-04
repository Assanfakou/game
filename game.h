#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <math.h>

#define FOV (M_PI / 3)
#define NUM_RAYS 60 
#define RAY_LENGTH 100

# ifndef COLOR
#  define COLORE "\033[0;33m"
# endif

# ifndef RESET
#  define RESET "\e[0m"
# endif


#define WIDTH 700
#define HEIGHT 700
#define TILE 50

#define GRE 0x0000FF00
#define RED 0x00FF0000
#define BLU 0x000000FF


#define ESC 65307
#define UP 119
#define DOWN 115
#define RIGHT 100
#define LEFT 97

typedef struct s_vector
{
	double x;
	double y;
}	t_vector;

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

typedef struct s_txtrs
{
	void *wall;
	int floor_color;
	int sky_color;
}	t_textrs;

typedef struct s_cub
{
	char **map;
	t_mlx *mlx;
	t_player *player;

}	t_cub;

void draw_line(t_mlx *mlx, int start_x, int start_y, int end_x, int end_y, int color);
void draw_fov(t_cub *game);
void draw_player(t_mlx *mlx, t_player *player);
void my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color);
