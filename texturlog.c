#include "game.h"

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