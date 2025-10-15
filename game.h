//#include "minilibx/mlx.h"
#include "mlx.h"
#include "libft/libft.h"
#include <math.h>
#include <sys/time.h>
#include "parse/parsing.h"

#define FOV (M_PI / 3)
#define RAY_LENGTH 50

# ifndef COLOR
#  define COLORE "\033[0;33m"
# endif

# ifndef RESET
#  define RESET "\e[0m"
# endif

#define TILEIM 12

#define WIDTH 1800
#define HEIGHT 1000
#define TILE 50
#define NUM_RAYS WIDTH 

#define WIDTHMAP 280
#define HEIGHTMAP 280

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

typedef struct s_image
{
	void *addr;
	void *buff;
	int bpp;
	int line_length;
	int endian;
	int width;
	int height;
}	t_image;

typedef struct s_render 
{
	void *mlx;
	void *win;
}	t_render;

typedef struct s_player
{
	t_vector *vec_p;
	t_vector *vec_d;
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

	t_game *data;
	t_render render;
	t_image image;
	t_image map_img;
	t_player *player;
}	t_cub;


typedef struct s_dda
{
	t_vector sidedist;
	t_vector raydir;
	t_vector deltadist;
    int mapx;
    int mapy;
    int stepx;
    int stepy;
}   t_dda;

typedef struct s_txtrs
{
	void *wall;
	int floor_color;
	int sky_color;
}	t_textrs;


void draw_line(t_image *image, int start_x, int start_y, int end_x, int end_y, int color);
void my_mlx_pixel_put(t_image *image, int x, int y, int color);

//ray_casting
void cast_all_rays(t_cub *game);
double cast_single_ray(t_cub *game, double ray_angle);


int	handle_keypress(int keycode);
int handle_keypres(int keycode, t_cub *game);
//mlx

t_image new_image(t_render render, int width, int height);
t_cub cub_init(t_game *game);


// map 

void drawLineVertical(t_image *image, int x, int height);
void drawLineHorizontal(t_image *image, int y, int width);
void draw_squar(t_image *image, int x, int y, int color);
void draw_grids(t_cub *game);
void draw_player(t_image *image, t_player *player);

void cast_all_map_rays(t_cub *game);

int	get_data(t_game *game, int argc, char **argv);
