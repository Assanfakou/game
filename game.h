/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:30:02 by hfakou            #+#    #+#             */
/*   Updated: 2025/11/01 21:03:00 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minilibx/mlx.h"
#ifndef GAME_H
# define GAME_H

# include "libft/libft.h"
# include "mlx.h"
# include "parse/parsing.h"
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>

# ifndef TILEIM
#  define TILEIM 12
# endif

# ifndef TILE
#  define TILE 60
# endif

# ifndef WIDTH
#  define WIDTH 1800
# endif

# ifndef HEIGHT
#  define HEIGHT 1000
# endif

# ifndef WIDTHMAP
#  define WIDTHMAP 280
# endif

# ifndef HEIGHTMAP
#  define HEIGHTMAP 280
# endif

# ifndef GRE
#  define GRE 0x0000FF00
# endif

# ifndef RED
#  define RED 0x00FF0000
# endif

# ifndef BLU
#  define BLU 0x000000FF
# endif

# ifndef ESC
#  define ESC 65307
# endif

# ifndef UP
#  define UP 119
# endif

# ifndef DOWN
#  define DOWN 115
# endif

# ifndef RIGHT
#  define RIGHT 100
# endif

# ifndef LEFT
#  define LEFT 97
# endif

# ifndef LFARR
#  define LFARR 65361
# endif

# ifndef RIGARR
#  define RIGARR 65363
# endif

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_vector_int
{
	int			x;
	int			y;
}				t_vector_int;

typedef struct s_line
{
	double		start_y;
	double		end_y;
}				t_line;

typedef struct s_image
{
	void		*addr;
	void		*buff;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_textures
{
	t_image		south;
	t_image		north;
	t_image		east;
	t_image		west;
}				t_textures;

typedef struct s_render
{
	void		*mlx;
	void		*win;
}				t_render;

typedef struct s_player
{
	t_vector	*vec_p;
	t_vector	*vec_d;
	double		angle;
	double		speed;
}				t_player;

typedef struct s_mlx
{
	void		*win;
	void		*mlx;
	void		*addr;
	void		*img;
	int			bpp;
	int			line_length;
	int			endian;
}				t_mlx;

typedef struct s_cub
{
	t_game		*data;
	t_render	render;
	t_image		image;
	t_image		map_img;
	t_textures	tex;
	t_player	*player;
	double		xwall;
	char		dir;
	int			ray;
	double		fov;
}				t_cub;

typedef struct s_dda
{
	t_vector	sidedist;
	t_vector	raydir;
	t_vector	deltadist;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
}				t_dda;

void			draw_line(t_image *image, t_vector_int start, t_vector_int end,
					int color);
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);
//ray_casting
void			cast_all_rays(t_cub *game);
double			cast_single_ray(t_cub *game, double ray_angle);
int				handle_keypress(int keycode, t_cub *cub);
t_image			new_image(t_render render, int width, int height);
t_cub			cub_init(t_game *game);
void			draw_line_vertical(t_image *image, int x, int height);
void			draw_line_horizontal(t_image *image, int y, int width);
void			draw_squar(t_image *image, int x, int y, int color);
void			draw_grids(t_cub *game);
void			draw_player(t_image *image, t_player *player);
int				get_data(t_game *game, int argc, char **argv);
void			wall_hight_draw(t_cub *game, double distance);
unsigned int	get_tex_color(t_image *tex, int x, int y);
double			get_distance(t_dda *var, t_cub *game, int flag);
void			draw_rays_map(t_cub *game, t_dda *var, int flag);
void			draw_the_vertical(t_cub *game, t_line line, int tex_x,
					double step);
void			set_tex_params(t_cub *game, double wall_hight, double *step,
					int *tex_x);
void			decide_where(t_dda *var, t_cub *game);
int				close_window(t_cub *game);
int				rgb_to_int(int *color);
double			get_delta_time(void);
void			move_afterward(t_cub *game);
void			move_back(t_cub *game);
void			rotate_left(t_cub *game);
void			rotate_right(t_cub *game);
void			update_point(t_vector_int *start, int *err, t_vector_int d,
					t_vector_int s);
void			draw_line(t_image *img, t_vector_int start, t_vector_int end,
					int color);
void			init_var(t_dda *var, t_cub *game, double angle);
void			which_wall(t_dda *var, t_cub *game, bool flag);
#endif