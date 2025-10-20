/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utilis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:03:14 by lzari             #+#    #+#             */
/*   Updated: 2025/10/20 19:03:15 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_padded_line(char *line, int width)
{
	return (pad_line_with_spaces(line, width));
}

int	process_map_line(t_game *game, char *line, int *line_idx, int *map_idx)
{
	if (ft_strlen(line) == 0)
	{
		(*line_idx)++;
		return (0);
	}
	game->map[*map_idx] = get_padded_line(line, game->map_width);
	if (!game->map[*map_idx])
		return (-1);
	(*map_idx)++;
	(*line_idx)++;
	return (1);
}

int	parse_map_array(char **lines, int start_idx, t_game *game)
{
	int	map_height;
	int	line_idx;
	int	map_idx;
	int	ret;

	map_height = count_map_lines(lines, start_idx);
	if (map_height == 0)
		return (0);
	game->map_width = get_max_line_length(lines, start_idx);
	game->map_height = map_height;
	game->map = malloc(sizeof(char *) * (map_height + 1));
	if (!game->map)
		return (0);
	line_idx = start_idx;
	map_idx = 0;
	while (map_idx < map_height && lines[line_idx])
	{
		ret = process_map_line(game, lines[line_idx], &line_idx, &map_idx);
		if (ret == -1)
			return (0);
	}
	game->map[map_idx] = NULL;
	return (1);
}

static int	handle_map_char(t_game *game, int i, int j, int *player_count)
{
	if (!is_valid_map_char(game->map[i][j]))
	{
		printf("Error: Invalid character '%c' at (%d,%d)\n",
			game->map[i][j],
			i,
			j);
		return (0);
	}
	if (is_player_char(game->map[i][j]))
	{
		(*player_count)++;
		game->player_x = j;
		game->player_y = i;
		game->player_dir = game->map[i][j];
	}
	return (1);
}

int	validate_map_characters(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (!handle_map_char(game, i, j, &player_count))
				return (0);
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		printf("Error: Found %d players, expected exactly 1\n", player_count);
		return (0);
	}
	return (1);
}
