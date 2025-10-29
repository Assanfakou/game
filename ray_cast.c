/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assankou <assankou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:00:43 by hfakou            #+#    #+#             */
/*   Updated: 2025/10/29 18:25:42 by assankou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/**
 * get_tex_color - Retrieves the color of a pixel from a texture
 * @texture: Pointer to the texture image
 * @x: X-coordinate in the texture
 * @y: Y-coordinate in the texture
 *
 * This function safely gets the color of the pixel at (x, y) in the texture.
 * It clamps x and y to the texture boundaries to avoid reading out of bounds.
 * The color is read directly from the image data using the formula:
 *   dest = addr + (y * line_length + x * (bpp / 8))
 * and then returned as an unsigned int.
 *
 * Return: The color of the pixel at (x, y) in ARGB format.
 */

unsigned int get_tex_color(t_image *texture, int x, int y)
{
	char	*dest;

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
/**
 * draw_the_vertical - Draws a vertical wall slice with the correct texture
 * @game: Pointer to the game structure containing images and textures
 * @i: X-coordinate of the screen column to draw
 * @line: Struct containing start_y and end_y for the wall slice
 * @tex_x: X-coordinate in the wall texture
 * @step: The vertical step to move in the texture per screen pixel
 * @texp: Starting Y position in the texture (usually 0 in your engine)
 *
 * This function loops from the top (start_y) to the bottom (end_y) of a wall
 * slice and draws each pixel on the screen. For each pixel, it calculates
 * which Y-coordinate of the wall texture to use and retrieves its color.
 * It then plots the pixel on the image using my_mlx_pixel_put. The function
 * selects the texture based on the wall direction (N, S, W, E).
 */

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
/**
 * set_texture_params - Sets the texture step and X coordinate for the wall
 * @game: Pointer to the game struct containing textures and direction
 * @wall_hight: Calculated height of the wall on screen
 * @step: Pointer to the step variable (height increment per pixel in texture)
 * @texX: Pointer to the X coordinate in the texture
 *
 * This function selects the correct texture based on wall direction
 * and calculates the horizontal texture coordinate (texX) and the
 * step size to sample texture vertically.
 */

void set_tex_params(t_cub *game, double wall_hight, double *step, int *tex_x)
{
	t_image *tex;

	if (game->dir == 'N')
		tex = &game->tex.north;
	else if (game->dir == 'S')
		tex = &game->tex.south;
	else if (game->dir == 'W')
		tex = &game->tex.west;
	else
		tex = &game->tex.east;
	*step = 1.0 * tex->height / wall_hight;
	*tex_x = (int)(game->xwall * tex->width);
}
/**
 * wall_height_calc - Calculates the wall height and draws vertical line
 * @game: Pointer to the game struct
 * @distance: Distance from the player to the wall
 * @i: Current column on the screen (x coordinate)
 *
 * This function calculates the height of a wall slice based on distance,
 * determines the texture parameters, and calls the function to draw
 * the vertical line with correct texture mapping.
 */

void wall_hight_cal(t_cub *game, double distance, int i)
{
	double wall_hight;
	t_line line;
	double step;
	double tex_pos;
	int tex_x;

	wall_hight = game->image.height * (TILE / distance);
	line.start_y = (game->image.height / 2) - (wall_hight / 2);
	line.end_y = (game->image.height / 2) + (wall_hight / 2);
	set_tex_params(game, wall_hight, &step, &tex_x);
	tex_pos = 0;//(line.start_y - game->image.height / 2 + wall_hight / 2) * step;
	draw_the_vertical(game, i, line, tex_x, step, tex_pos);
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
		wall_hight_cal(game, distance, i);
		i++;
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

void decide_where(t_dda *var, t_cub *game)
{
	var->deltadist.x = TILE / fabs(var->raydir.x);
	var->deltadist.y = TILE / fabs(var->raydir.y);
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
/**
 * draw_rays_map - Draws a single ray on the 2D minimap
 * @game: Pointer to the game structure containing player and map info
 * @var: Pointer to the DDA structure with ray information
 * @flag: Determines which side of the wall was hit (1 for vertical, 0 for horizontal)
 *
 * This function calculates the endpoint of a ray based on DDA distances
 * and draws a line from the player's position to the hit point on the minimap.
 * It scales the coordinates to the minimap resolution using TILEIM.
 */

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
