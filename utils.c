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

unsigned int	get_tex_color(t_image *texture, int x, int y)
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
	return (*(unsigned int *)(dest));
}

int	rgb_to_int(int *color)
{
	int	collor;
	int r;
	int g;
	int b;

	r = color[0];
	g = color[1];
	b = color[2];
	collor = (r << 16) | (g << 8) | b;
	return (collor);
}

double	get_delta_time(void)
{
	static struct timeval	last_time = {0, 0};
	struct timeval			current_time;
	double					delta;

	gettimeofday(&current_time, NULL);
	if (last_time.tv_sec == 0 && last_time.tv_usec == 0)
		last_time = current_time;
	delta = (current_time.tv_sec - last_time.tv_sec) +
		(current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	last_time = current_time;
	return (delta);
}