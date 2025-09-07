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
		wall_hight = TILE / distance * (prejection_plane);
		start_y = (HEIGHT / 2) - (wall_hight / 2);
		end_y = (HEIGHT / 2) + (wall_hight / 2);
		draw_line(game->mlx, i, start_y, i, end_y, BLU);
		i++;
	}
}

double cast_single_ray(t_cub *game, double angle)
{
	double ray_x;
	double ray_y;
	double step_x;
	double step_y;

	ray_x = game->player->x;
	ray_y = game->player->y;
	step_x = cos(angle);
	step_y = sin(angle);
	while (1)
	{
		ray_x += step_x;
		ray_y += step_y;
		if (game->map[(int)ray_y / TILE][(int)ray_x / TILE] == '1')
			return (sqrt(pow(ray_x - game->player->x, 2) + pow(ray_y - game->player->y, 2)));
	}
}
