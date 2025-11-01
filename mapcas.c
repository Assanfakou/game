#include "game.h"

/**
 * draw_rays_map - Draws a single ray on the 2D minimap
 * @game: Pointer to the game structure containing player and map info
 * @var: Pointer to the DDA structure with ray information
 * @flag: Determines which side of the wall was hit (1 for vertical,
		0 for horizontal)
 *
 * This function calculates the endpoint of a ray based on DDA distances
 * and draws a line from the player's position to the hit point on the minimap.
 * It scales the coordinates to the minimap resolution using TILEIM.
 */

void	draw_rays_map(t_cub *game, t_dda *var, int flag)
{
	double distance;
	t_vector ve;

	if (flag)
	{
		distance = var->sidedist.x - var->deltadist.x;
		ve.x = game->player->vec_p->x + var->raydir.x * distance;
		ve.y = game->player->vec_p->y + var->raydir.y * distance;
		draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM,
				game->player->vec_p->y / TILE * TILEIM, ve.x / TILE * TILEIM,
				ve.y / TILE * TILEIM, GRE);
	}
	else
	{
		distance = var->sidedist.y - var->deltadist.y;
		ve.x = game->player->vec_p->x + var->raydir.x * distance;
		ve.y = game->player->vec_p->y + var->raydir.y * distance;
		draw_line(&game->map_img, game->player->vec_p->x / TILE * TILEIM,
				game->player->vec_p->y / TILE * TILEIM, ve.x / TILE * TILEIM,
				ve.y / TILE * TILEIM, GRE);
	}
}
