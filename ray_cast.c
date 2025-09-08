#include "game.h"

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
		distance = cast_single_ray(game, ray_angle);
		wall_hight = TILE / distance * (prejection_plane / 2);
		start_y = (HEIGHT / 2) - (wall_hight / 2);
		end_y = (HEIGHT / 2) + (wall_hight / 2);
		draw_line(game->mlx, i, start_y, i, end_y, BLU);
		i++;
	}
}


double cast_single_ray(t_cub *game, double angle)
{
    t_dda var;

    var.raydirx = cos(angle);
    var.raydiry = sin(angle);
    var.mapx = (int)(game->player->x / TILE);
    var.mapy = (int)(game->player->y / TILE);
    var.deltadistx = fabs(1 / var.raydirx);
    var.deltadisty = fabs(1 / var.raydiry);
    if (var.raydirx < 0)
    {
        var.stepx = -1;
        var.sidedistx = (game->player->x - var.mapx * TILE) / fabs(var.raydirx);
    }
    else
    {
        var.stepx = 1;
        var.sidedistx = ((var.mapx + 1) * TILE - game->player->x) / fabs(var.raydirx);
    }
    if (var.raydiry < 0)
    {
        var.stepy = -1;
        var.sidedisty = (game->player->y - var.mapy * TILE) / fabs(var.raydiry);
    }
    else
    {
        var.stepy = 1;
        var.sidedisty = ((var.mapy + 1) * TILE - game->player->y) / fabs(var.raydiry);
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

