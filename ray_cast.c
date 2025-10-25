/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:00:43 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/25 17:10:31 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

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

void draw_the_vertical(t_cub *game, int i, t_line line, int tex_x, double step, double texp)
{
	int y;
	int tex_y;
	double tex_pos;
	unsigned int color;

	tex_pos = texp;
	y = line.start_y;
	while (y < line.end_y)
	{
		tex_y = tex_pos;
		tex_pos += step;
		if (game->dir == 'S')
			color = get_tex_color(&game->tex.south, tex_x, tex_y);
		else if (game->dir == 'N')
			color = get_tex_color(&game->tex.north, tex_x, tex_y);
		else if (game->dir == 'W')
			color = get_tex_color(&game->tex.west, tex_x, tex_y);
		else
			color = get_tex_color(&game->tex.east, tex_x, tex_y);
		my_mlx_pixel_put(&game->image, i, y, color);
		y++;
	}
}

void wall_hight_draw(t_cub *game, double distance, int i)
{
	double wall_hight;
	t_line line;
	double step;
	double tex_pos;
	int texX;

	wall_hight = game->image.height * (TILE / distance);
	line.start_y = (game->image.height / 2) - (wall_hight / 2);
	line.end_y = (game->image.height / 2) + (wall_hight / 2);
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
	else
	{
		step = 1.0 * game->tex.east.height / wall_hight;
		texX = (int)(game->xwall * game->tex.east.width);
	}
	tex_pos = (line.start_y - game->image.height / 2 + wall_hight / 2) * step;
	draw_the_vertical(game, i, line, texX, step, tex_pos);
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
	var->mapx = (int)(game->player->vec_p->x / TILE);
	var->mapy = (int)(game->player->vec_p->y / TILE);

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

void draw_rays_map(t_cub *game, t_dda *var, int flag)
{
	double distance;
	t_vector ve;

	if (flag)
	{
		distance = var->sidedist.x - var->deltadist.x;
		ve.x = game->player->vec_p->x + var->raydir.x * distance;
		ve.y = game->player->vec_p->y + var->raydir.y * distance;
		draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM, game->player->vec_p->y / TILE * TILEIM,ve.x/TILE *TILEIM, ve.y /TILE *TILEIM, GRE); 
	}
	else
	{
		distance = var->sidedist.y - var->deltadist.y;
		ve.x = game->player->vec_p->x + var->raydir.x * distance;
		ve.y = game->player->vec_p->y + var->raydir.y * distance;
		draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM, game->player->vec_p->y / TILE * TILEIM,ve.x / TILE * TILEIM, ve.y / TILE * TILEIM, GRE); 
	}
}
	
double cast_single_ray(t_cub *game, double angle)
{
	t_dda var;

	var.raydir.x = cos(angle);
	var.raydir.y = sin(angle);
	decide_where(&var, game);
	while (1)
	{
		if (var.sidedist.x < var.sidedist.y)
		{
			var.sidedist.x += var.deltadist.x;
			var.mapx += var.stepx;
			if (game->data->map[var.mapy][var.mapx] == '1')
				return (get_distance(&var, game, 1) * cos(angle - game->player->angle));
		}
		else
		{
			var.sidedist.y += var.deltadist.y;
			var.mapy += var.stepy;
			if (game->data->map[var.mapy][var.mapx] == '1')
				return (get_distance(&var, game, 0) * cos(angle - game->player->angle));
		}
	}
}

double get_distance(t_dda *var, t_cub *game, int flag)
{
	if (!flag)
	{
		if (var->raydir.y > 0)
			game->dir = 'S';
		else
			game->dir = 'N';
		draw_rays_map(game, var, flag);
		game->xwall = game->player->vec_p->x + (var->sidedist.y - var->deltadist.y) * var->raydir.x;
		game->xwall /= TILE;
		game->xwall -= floor(game->xwall);
		return ((var->sidedist.y - var->deltadist.y));
	}
	else
	{
		if (var->raydir.x > 0)
			game->dir = 'E';
		else
			game->dir = 'W';
		draw_rays_map(game, var, flag);
		game->xwall = game->player->vec_p->y + (var->sidedist.x - var->deltadist.x) * var->raydir.y;
		game->xwall /= TILE;
		game->xwall -= floor(game->xwall);
		return (var->sidedist.x - var->deltadist.x);
	}
}
