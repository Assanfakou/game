/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:00:43 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/03 14:35:53 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void cast_single_ray_map(t_cub *game, double angle)
{
    double ray_x = game->player->vec_p->x;
    double ray_y = game->player->vec_p->y;
    double step_x = cos(angle) * 2; // step size, smaller = smoother line
    double step_y = sin(angle) * 2;

    while (1)
    {
        ray_x += step_x;
        ray_y += step_y;

        int map_x = (int)(ray_x / TILE);
        int map_y = (int)(ray_y / TILE);

        if (game->map[map_y][map_x] == '1')
            break;

        // scale world coords -> minimap coords
        draw_line(
            &game->map_img,
            (int)(game->player->vec_p->x / TILE * TILEIM),
            (int)(game->player->vec_p->y / TILE * TILEIM),
            (int)(ray_x / TILE * TILEIM),
            (int)(ray_y / TILE * TILEIM),
            GRE
        );
    }
}
/*
void cast_single_ray_map(t_cub *game, double angle)
{
	double ray_x = game->player->x;
	double ray_y = game->player->y;
	double step_x = cos(angle);
	double step_y = sin(angle);

	while (1)
	{
		ray_x += step_x;
		ray_y += step_y;
		if (game->map[(int)ray_y / TILEIM][(int)ray_x / TILEIM] == '1')
			break;
		draw_line(&game->map_img, game->player->x / TILEIM, game->player->y / TILEIM, (int)ray_x, (int)ray_y, GRE);
	}
}
*/

void cast_all_rays(t_cub *game)
{
	double ray_angle;
	int i;
	double distance;
	double prejection_plane = (WIDTH / 2) / (FOV / 2);
	double wall_hight;
	double start_y;
	double end_y;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = game->player->angle - (FOV / 2) + i * (FOV / NUM_RAYS);
		//cast_single_ray_map(game, ray_angle);
		distance = cast_single_ray(game, ray_angle);
		wall_hight = TILE / distance * (prejection_plane / 2);
		start_y = (HEIGHT / 2) - (wall_hight / 2);
		end_y = (HEIGHT / 2) + (wall_hight / 2);
		draw_line(&game->image, i, start_y, i, end_y, BLU);
		i++;
	}
}

void cast_all_map_rays(t_cub *game)
{
	double ray_angle;
	int i;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = game->player->angle - (FOV / 2) + i * (FOV / NUM_RAYS);
		cast_single_ray_map(game, ray_angle);
		i++;
	}
}

double cast_single_ray(t_cub *game, double angle)
{
	t_dda var;

	var.raydirx = cos(angle);
	var.raydiry = sin(angle);
	var.mapx = (int)(game->player->vec_p->x / TILE);
	var.mapy = (int)(game->player->vec_p->y / TILE);
	var.deltadistx = fabs(1 / var.raydirx);
	var.deltadisty = fabs(1 / var.raydiry);
	if (var.raydirx < 0)
	{
		var.stepx = -1;
		var.sidedistx = (game->player->vec_p->x - var.mapx * TILE) / fabs(var.raydirx);
	}
	else
	{
		var.stepx = 1;
		var.sidedistx = ((var.mapx + 1) * TILE - game->player->vec_p->x) / fabs(var.raydirx);
	}
	if (var.raydiry < 0)
	{
		var.stepy = -1;
		var.sidedisty = (game->player->vec_p->y - var.mapy * TILE) / fabs(var.raydiry);
	}
	else
	{
		var.stepy = 1;
		var.sidedisty = ((var.mapy + 1) * TILE - game->player->vec_p->y) / fabs(var.raydiry);
	}
	while (1)
	{
		if (var.sidedistx < var.sidedisty)
		{
			var.sidedistx += var.deltadistx * TILE;
			var.mapx += var.stepx;
			if (game->map[var.mapy][var.mapx] == '1')
				return (var.sidedistx - var.deltadistx * TILE);
		}
		else
		{
			var.sidedisty += var.deltadisty * TILE;
			var.mapy += var.stepy;
			if (game->map[var.mapy][var.mapx] == '1')
				return (var.sidedisty - var.deltadisty * TILE);
		}
	}
}
