#include "minilibx/mlx.h"
//#include "mlx.h"
#include "libft/libft.h"
#include <math.h>

#define FOV (M_PI / 3)
#define RAY_LENGTH 50

# ifndef COLOR
#  define COLORE "\033[0;33m"
# endif

# ifndef RESET
#  define RESET "\e[0m"
# endif


#define WIDTH 1500
#define HEIGHT 1000
#define TILE 50
#define NUM_RAYS WIDTH 

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

typedef struct s_cub
{
	char **map;
	t_mlx *mlx;
	t_mlx *map_image;
	t_player *player;
}	t_cub;


typedef struct s_dda
{
    double raydirx;
    double raydiry;
    int mapx;
    int mapy;
    double sidedistx;
    double sidedisty;
    double deltadistx;
    double deltadisty;
    int stepx;
    int stepy;
}   t_dda;

typedef struct s_txtrs
{
	void *wall;
	int floor_color;
	int sky_color;
}	t_textrs;

void mlx_ini(t_mlx *mlx, t_mlx *map_image);

void draw_line(t_mlx *mlx, int start_x, int start_y, int end_x, int end_y, int color);
void my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color);

//ray_casting
void cast_all_rays(t_cub *game);
double cast_single_ray(t_cub *game, double ray_angle);


int	handle_keypress(int keycode);
int handle_keypres(int keycode, t_cub *game);



// map 

void drawLineVertical(t_mlx *mlx, int x, int height);
void drawLineHorizontal(t_mlx *mlx, int y, int width);
void draw_squar(t_mlx *mlx, int x, int y, int color);
void draw_grids(t_mlx *mlx);
void draw_player(t_mlx *mlx, t_player *player);

