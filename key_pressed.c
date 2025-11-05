/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 16:17:38 by hfakou            #+#    #+#             */
/*   Updated: 2025/11/05 16:09:06 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	move_afterward(t_cub *game)
{
	t_vector	new;
	t_player	*player;
	int			map_x;
	int			map_y;

	player = game->player;
	new.y = player->vec_p->y + player->vec_d->y * player->speed;
	new.x = player->vec_p->x + player->vec_d->x * player->speed;
	map_y = (int)(new.y / TILE);
	map_x = (int)(new.x / TILE);
	if (game->data->map[map_y][map_x] != '1')
	{
		player->vec_p->x = new.x;
		player->vec_p->y = new.y;
	}
}

void	move_back(t_cub *game)
{
	t_vector	new;
	t_player	*player;
	int			map_x;
	int			map_y;

	player = game->player;
	new.y = player->vec_p->y - player->vec_d->y * player->speed;
	new.x = player->vec_p->x - player->vec_d->x * player->speed;
	map_y = (int)(new.y / TILE);
	map_x = (int)(new.x / TILE);
	if (game->data->map[map_y][map_x] != '1')
	{
		player->vec_p->x = new.x;
		player->vec_p->y = new.y;
	}
}

void	rotate_left(t_cub *game)
{
	t_player	*player;

	player = game->player;
	player->angle -= 0.1;
	player->vec_d->x = cos(player->angle);
	player->vec_d->y = sin(player->angle);
}

void	rotate_right(t_cub *game)
{
	t_player	*player;

	player = game->player;
	player->angle += 0.1;
	player->vec_d->x = cos(player->angle);
	player->vec_d->y = sin(player->angle);
}

int	handle_keypress(int keycode, t_cub *game)
{
	if (keycode == UP)
		move_afterward(game);
	if (keycode == DOWN)
		move_back(game);
	if (keycode == LEFT || keycode == LFARR)
		rotate_left(game);
	if (keycode == RIGHT || keycode == RIGARR)
		rotate_right(game);
	if (keycode == ESC)
		close_window(game);
	if (keycode == M)
		m_flag = true;	
	if (keycode == N)
		m_flag = false;
	return (0);
}
