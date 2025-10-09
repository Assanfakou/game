/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:00:43 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/09 21:57:30 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

double distance;
t_vector ve;
void cast_all_rays(t_cub *game)
{
	double ray_angle;
	int	i;
	double distance;
	double prejection_plane = (game->data->map_width * TILE / 2) / (FOV / 2);
	double wall_hight;
	double start_y;
	double end_y;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = game->player->angle - (FOV / 2) + i * (FOV / NUM_RAYS);
		// printf("angle %f\n", ray_angle);
		distance = cast_single_ray(game, ray_angle);

		wall_hight = TILE / distance * (prejection_plane / 2);
		start_y = (game->data->map_height * TILE / 2) - (wall_hight / 2);
		end_y = (game->data->map_height * TILE / 2) + (wall_hight / 2);
		draw_line(&game->image, i, start_y, i, end_y, 0xFFFFFF);
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
				distance = var.sidedistx - var.deltadistx * TILE;
				ve.x = game->player->vec_p->x + var.raydirx * distance;
				ve.y = game->player->vec_p->y + var.raydiry * distance;
				draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM, game->player->vec_p->y / TILE * TILEIM,ve.x/TILE *TILEIM, ve.y /TILE *TILEIM, GRE); 
				return (var.sidedistx - var.deltadistx * TILE);
			}
		}
		else
		{
			// printf("not here\n");
			var.sidedisty += var.deltadisty * TILE;
			var.mapy += var.stepy;
			if (game->data->map[var.mapy][var.mapx] == '1')
			{
				distance = var.sidedisty - var.deltadisty * TILE;
				ve.x = game->player->vec_p->x + var.raydirx * distance;
				ve.y = game->player->vec_p->y + var.raydiry * distance;
				draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM, game->player->vec_p->y / TILE * TILEIM,ve.x / TILE * TILEIM, ve.y / TILE * TILEIM, GRE); 
				return (var.sidedisty - var.deltadisty * TILE);
			}
		}

	}
}
