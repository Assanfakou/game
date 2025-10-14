/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:00:43 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/14 01:30:55 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void wall_hight_draw(t_cub *game, double distance, int i)
{
	double wall_hight;
	double start_y;
	double end_y;
	int y;

	wall_hight = game->image.height * (TILE / distance);
	start_y = (game->image.height / 2) - (wall_hight / 2);
	end_y = (game->image.height / 2) + (wall_hight / 2);
	y = start_y;
	while (y <= end_y)
	{
		my_mlx_pixel_put(&game->image, i, y, 0xFFFFFFF);
		y++;
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
	var->deltadistx = fabs(1 / var->raydirx);
	var->deltadisty = fabs(1 / var->raydiry);
	if (var->raydirx < 0)
	{
		var->stepx = -1;
		var->sidedistx = (game->player->vec_p->x - var->mapx * TILE) / fabs(var->raydirx);
	}
	else
	{
		var->stepx = 1;
		var->sidedistx = ((var->mapx + 1) * TILE - game->player->vec_p->x) / fabs(var->raydirx);
	}
	if (var->raydiry < 0)
	{
		var->stepy = -1;
		var->sidedisty = (game->player->vec_p->y - var->mapy * TILE) / fabs(var->raydiry);
	}
	else
	{
		var->stepy = 1;
		var->sidedisty = ((var->mapy + 1) * TILE - game->player->vec_p->y) / fabs(var->raydiry);
	}
}
void draw_rays_map(t_cub *game, t_dda var, int flag)
{
	double distance;
	t_vector ve;

	if (flag)
	{
		distance = var.sidedistx - var.deltadistx * TILE;
		ve.x = game->player->vec_p->x + var.raydirx * distance;
		ve.y = game->player->vec_p->y + var.raydiry * distance;
		draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM, game->player->vec_p->y / TILE * TILEIM,ve.x/TILE *TILEIM, ve.y /TILE *TILEIM, GRE); 
	}
	else
	{
		distance = var.sidedisty - var.deltadisty * TILE;
		ve.x = game->player->vec_p->x + var.raydirx * distance;
		ve.y = game->player->vec_p->y + var.raydiry * distance;
		draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM, game->player->vec_p->y / TILE * TILEIM,ve.x / TILE * TILEIM, ve.y / TILE * TILEIM, GRE); 
	}
}
	
double cast_single_ray(t_cub *game, double angle)
{
	t_dda var;

	var.raydirx = cos(angle);
	var.raydiry = sin(angle);
	var.mapx = (int)(game->player->vec_p->x / TILE);
	var.mapy = (int)(game->player->vec_p->y / TILE);

	decide_where(&var, game);
	while (1)
	{
		if (var.sidedistx < var.sidedisty)
		{
			var.sidedistx += var.deltadistx * TILE;
			var.mapx += var.stepx;
			if (game->data->map[var.mapy][var.mapx] == '1')
			{
				draw_rays_map(game, var, 1);
				return ((var.sidedistx - var.deltadistx * TILE) * cos(angle - game->player->angle));
			}
		}
		else
		{
			var.sidedisty += var.deltadisty * TILE;
			var.mapy += var.stepy;
			if (game->data->map[var.mapy][var.mapx] == '1')
			{
				draw_rays_map(game, var, 0);
				// printf("fisheye :%f\n", cos(angle - game->player->angle));
				return ((var.sidedisty - var.deltadisty * TILE) * cos(angle - game->player->angle));
			}
		}

	}
}
