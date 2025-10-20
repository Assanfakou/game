/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_part2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:55:46 by lzari             #+#    #+#             */
/*   Updated: 2025/10/20 16:55:47 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_position_walls(t_game *game, int y, int x)
{
	if (y == 0 || y == game->map_height - 1)
		return (0);
	if (x == 0 || x == game->map_width - 1)
		return (0);
	if (game->map[y - 1][x] == ' ' || game->map[y + 1][x] == ' ')
		return (0);
	if (game->map[y][x - 1] == ' ' || game->map[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	validate_map_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (is_walkable(game->map[i][j]))
			{
				if (!check_position_walls(game, i, j))
				{
					printf("Error: Map not closed at position (%d,%d)\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	parse_map(char **lines, int start_idx, t_game *game)
{
	if (!parse_map_array(lines, start_idx, game))
	{
		printf("Error: Failed to parse map array\n");
		return (0);
	}
	if (!validate_map_characters(game))
		return (0);
	if (!validate_map_walls(game))
		return (0);
	return (1);
}
