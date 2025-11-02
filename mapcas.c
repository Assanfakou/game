/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:16:15 by hfakou            #+#    #+#             */
/*   Updated: 2025/11/01 17:18:26 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	double			dis;
	t_vector_int	start;
	t_vector_int	end;

	if (flag)
	{
		dis = var->sidedist.x - var->deltadist.x;
		start.x = game->player->vec_p->x / TILE * TILEIM;
		start.y = game->player->vec_p->y / TILE * TILEIM;
		end.x = (game->player->vec_p->x + var->raydir.x * dis) / TILE * TILEIM;
		end.y = (game->player->vec_p->y + var->raydir.y * dis) / TILE * TILEIM;
		draw_line(&game->map_img, start, end, GRE);
	}
	else
	{
		dis = var->sidedist.y - var->deltadist.y;
		start.x = game->player->vec_p->x / TILE * TILEIM;
		start.y = game->player->vec_p->y / TILE * TILEIM;
		end.x = (game->player->vec_p->x + var->raydir.x * dis) / TILE * TILEIM;
		end.y = (game->player->vec_p->y + var->raydir.y * dis) / TILE * TILEIM;
		draw_line(&game->map_img, start, end, GRE);
	}
}
