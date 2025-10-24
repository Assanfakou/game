/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:00:43 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/24 20:34:16 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
bool hit = false;
t_vector wallx;
unsigned int get_tex_color(t_image *texture, int x, int y)
{
	char *dest;
	if (x < 0)
		x = 0;
	if (x >= texture->width)
		x = texture->width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->height)
		y = texture->height - 1;
	dest = texture->addr + (y * texture->line_length + x * (texture->bpp / 8));
	return *(unsigned int *)(dest);
}
void wall_hight_draw(t_cub *game, double distance, int i)
{
    double wall_hight = game->image.height * (100 / distance);
    double start_y = (game->image.height / 2) - (wall_hight / 2);
    double end_y = (game->image.height / 2) + (wall_hight / 2);
    double step = 1.0 * game->tex.east.height / wall_hight;
    double tex_pos;
    int texX = (int)(game->xwall * game->tex.east.width);
	unsigned int color;
	if (game->dir == 'S')
	{
    	step = 1.0 * game->tex.south.height / wall_hight;
    	texX = (int)(game->xwall * game->tex.south.width);
	}
	else if (game->dir == 'N')
	{
    	step = 1.0 * game->tex.north.height / wall_hight;
    	texX = (int)(game->xwall * game->tex.north.width);
	}
	else if (game->dir == 'W')
	{
    	step = 1.0 * game->tex.west.height / wall_hight;
    	texX = (int)(game->xwall * game->tex.west.width);
	}
	else if (game->dir == 'E')
	{
    	step = 1.0 * game->tex.east.height / wall_hight;
    	texX = (int)(game->xwall * game->tex.east.width);
	}
	
	tex_pos = (start_y - game->image.height / 2 + wall_hight / 2) * step;
    for (int y = start_y; y < end_y; y++)
    {
        int texY = (int)tex_pos;
        tex_pos += step;
		if (game->dir == 'S')
        	color = get_tex_color(&game->tex.south, texX, texY);
		else if (game->dir == 'N')
        	color = get_tex_color(&game->tex.north, texX, texY);
		else if (game->dir == 'W')
        	color = get_tex_color(&game->tex.west, texX, texY);
		else
        	color = get_tex_color(&game->tex.east, texX, texY);

        my_mlx_pixel_put(&game->image, i, y, color);
    }
}
void cast_all_rays(t_cub *game)
{
	double ray_angle;
	int	i;
	double distance;

	i = 0;
	while (i < game->image.width)
	{
		ray_angle = game->player->angle - (FOV / 2) + i * (FOV / game->image.width);
		distance = cast_single_ray(game, ray_angle);
		wall_hight_draw(game, distance, i);
		i++;
	}
}

void decide_where(t_dda *var, t_cub *game)
{
	var->deltadist.x = fabs(1 / var->raydir.x) * TILE;
	var->deltadist.y = fabs(1 / var->raydir.y) * TILE;
	if (var->raydir.x < 0)
	{
		var->stepx = -1;
		var->sidedist.x = (game->player->vec_p->x - var->mapx * TILE) / fabs(var->raydir.x);
	}
	else
	{
		var->stepx = 1;
		var->sidedist.x = ((var->mapx + 1) * TILE - game->player->vec_p->x) / fabs(var->raydir.x);
	}
	if (var->raydir.y < 0)
	{
		var->stepy = -1;
		var->sidedist.y = (game->player->vec_p->y - var->mapy * TILE) / fabs(var->raydir.y);
	}
	else
	{
		var->stepy = 1;
		var->sidedist.y = ((var->mapy + 1) * TILE - game->player->vec_p->y) / fabs(var->raydir.y);
	}
}

void draw_rays_map(t_cub *game, t_dda var, int flag)
{
	double distance;
	t_vector ve;

	if (flag)
	{
		distance = var.sidedist.x - var.deltadist.x;
		ve.x = game->player->vec_p->x + var.raydir.x * distance;
		ve.y = game->player->vec_p->y + var.raydir.y * distance;
		draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM, game->player->vec_p->y / TILE * TILEIM,ve.x/TILE *TILEIM, ve.y /TILE *TILEIM, GRE); 
	}
	else
	{
		distance = var.sidedist.y - var.deltadist.y;
		ve.x = game->player->vec_p->x + var.raydir.x * distance;
		ve.y = game->player->vec_p->y + var.raydir.y * distance;
		draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM, game->player->vec_p->y / TILE * TILEIM,ve.x / TILE * TILEIM, ve.y / TILE * TILEIM, GRE); 
	}
}
	
double cast_single_ray(t_cub *game, double angle)
{
	t_dda var;

	var.raydir.x = cos(angle);
	var.raydir.y = sin(angle);
	var.mapx = (int)(game->player->vec_p->x / TILE);
	var.mapy = (int)(game->player->vec_p->y / TILE);
	// printf("name : %s\n", game->data->east_texture);

	decide_where(&var, game);
	while (1)
	{
		if (var.sidedist.x < var.sidedist.y)
		{
			var.sidedist.x += var.deltadist.x;
			var.mapx += var.stepx;
			if (game->data->map[var.mapy][var.mapx] == '1')
			{
				hit = false;
				if (var.raydir.x > 0)
					game->dir = 'E';
				else
					game->dir = 'W';
				draw_rays_map(game, var, 1);
				wallx.x = game->player->vec_p->y + (var.sidedist.x - var.deltadist.x) * var.raydir.y;
				wallx.x /= TILE;
				wallx.x -= floor(wallx.x);
				game->xwall = wallx.x;
				return ((var.sidedist.x - var.deltadist.x) * cos(angle - game->player->angle));
			}
		}
		else
		{
			var.sidedist.y += var.deltadist.y;
			var.mapy += var.stepy;
			if (game->data->map[var.mapy][var.mapx] == '1')
			{
				hit = true;	
				if (var.raydir.y > 0)
					game->dir = 'S';
				else
					game->dir = 'N';
				draw_rays_map(game, var, 0);
				wallx.x = game->player->vec_p->x + (var.sidedist.y - var.deltadist.y) * var.raydir.x;
				wallx.x /= TILE;
				wallx.x -= floor(wallx.x);
				game->xwall = wallx.x;
				return ((var.sidedist.y - var.deltadist.y) * cos(angle - game->player->angle));
			}
		}

	}
}
