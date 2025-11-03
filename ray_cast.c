/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:00:43 by hfakou            #+#    #+#             */
/*   Updated: 2025/11/03 09:41:07 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/**
 * wall_height_calc - Calculates the wall height and draws vertical line
 * @game: Pointer to the game struct
 * @distance: Distance from the player to the wall
 *
 * This function calculates the height of a wall slice based on distance,
 * determines the texture parameters, and calls the function to draw
 * the vertical line with correct texture mapping.
 */

void	wall_hight_cal(t_cub *game, double distance)
{
	double	wall_hight;
	t_line	line;
	double	step;
	int		tex_x;

	wall_hight = game->image.height * (TILE / distance);
	line.start_y = (game->image.height / 2) - (wall_hight / 2);
	line.end_y = (game->image.height / 2) + (wall_hight / 2);
	set_tex_params(game, wall_hight, &step, &tex_x);
	draw_the_vertical(game, line, tex_x, step);
}

/**
 * cast_all_rays - Casts a ray for every vertical screen column
 * @game: Pointer to the game structure containing player and map info
 *
 * This function loops through every column of the screen and calculates
 * the corresponding ray angle based on the player's viewing angle and
 * the field of view (FOV). For each ray, it calls cast_single_ray to
 * find the distance to the nearest wall and then calls wall_height_cal
 * to draw the vertical wall slice for that column.
 */

void	cast_all_rays(t_cub *game)
{
	double	ray_angle;
	int		i;
	double	distance;

	i = 0;
	while (i < game->image.width)
	{
		ray_angle = game->player->angle - (game->fov / 2) + i * (game->fov
				/ game->image.width);
		distance = cast_single_ray(game, ray_angle);
		game->ray = i;
		wall_hight_cal(game, distance);
		i++;
	}
}

/**
 * cast_single_ray - Casts a ray and finds the distance to the first wall
 * @game: Pointer to the game structure containing player and map info
 * @angle: Angle of the ray in radians
 *
 * This function initializes a DDA ray with the given angle and steps through
 * the map grid using the Digital Differential Analyzer (DDA) algorithm until
 * it hits a wall. For each step, it chooses whether to move in the x or y
 * direction based on which side distance is smaller. Once a wall is hit, it
 * calculates the perpendicular distance to the wall (correcting for fish-eye
 * effect) and returns it.
 *
 * Return: Perpendicular distance from the player to the first wall hit.
 */

double	cast_single_ray(t_cub *game, double angle)
{
	t_dda	var;

	init_var(&var, game, angle);
	decide_where(&var, game);
	while (1)
	{
		if (var.sidedist.x < var.sidedist.y)
		{
			var.sidedist.x += var.deltadist.x;
			var.mapx += var.stepx;
			if (game->data->map[var.mapy][var.mapx] == '1')
				return (get_distance(&var, game, 1) * cos(angle
						- game->player->angle));
		}
		else
		{
			var.sidedist.y += var.deltadist.y;
			var.mapy += var.stepy;
			if (game->data->map[var.mapy][var.mapx] == '1')
				return (get_distance(&var, game, 0) * cos(angle
						- game->player->angle));
		}
	}
}
/**
 * decide_where - Initializes DDA variables 
 * @var: Pointer to the DDA struct containing ray information
 * @game: Pointer to the game structure containing player position
 *
 * This function calculates the distance increments (deltadist) for the ray
 * in x and y directions, determines the current map square of the player,
 * and sets the step direction and initial side distances (sidedist) for
 * the Digital Differential Analyzer algorithm. These values are
 * used to efficiently step through the map grid to find wall intersections.
 */

void	decide_where(t_dda *var, t_cub *game)
{
	if (var->raydir.x < 0)
	{
		var->stepx = -1;
		var->sidedist.x = (game->player->vec_p->x - var->mapx * TILE)
			/ fabs(var->raydir.x);
	}
	else
	{
		var->stepx = 1;
		var->sidedist.x = ((var->mapx + 1) * TILE - game->player->vec_p->x)
			/ fabs(var->raydir.x);
	}
	if (var->raydir.y < 0)
	{
		var->stepy = -1;
		var->sidedist.y = (game->player->vec_p->y - var->mapy * TILE)
			/ fabs(var->raydir.y);
	}
	else
	{
		var->stepy = 1;
		var->sidedist.y = ((var->mapy + 1) * TILE - game->player->vec_p->y)
			/ fabs(var->raydir.y);
	}
}
/**
 * get_distance - Calculates the distance from the player to a wall hit
 * @var: Pointer to the DDA structure containing ray info
 * @game: Pointer to the game structure
 * @flag: Indicates which side was hit (0 = horizontal, 1 = vertical)
 *
 * This function determines the wall direction based on the ray direction,
 * draws the ray on the minimap, calculates the exact hit point along the
 * wall (xwall) for texture mapping, and returns the distance from the
 * player to the wall hit.
 *
 * Return: Distance from the player to the wall along the ray.
 */

double	get_distance(t_dda *var, t_cub *game, int flag)
{
	if (!flag)
	{
		which_wall(var, game, true);
		draw_rays_map(game, var, flag);
		game->xwall = game->player->vec_p->x + (var->sidedist.y
				- var->deltadist.y) * var->raydir.x;
		game->xwall /= TILE;
		game->xwall -= floor(game->xwall);
		return (var->sidedist.y - var->deltadist.y);
	}
	else
	{
		which_wall(var, game, false);
		draw_rays_map(game, var, flag);
		game->xwall = game->player->vec_p->y + (var->sidedist.x
				- var->deltadist.x) * var->raydir.y;
		game->xwall /= TILE;
		game->xwall -= floor(game->xwall);
		return (var->sidedist.x - var->deltadist.x);
	}
}
