/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:40:32 by lzari             #+#    #+#             */
/*   Updated: 2025/10/20 15:40:34 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_map_lines(char **lines, int start_idx)
{
	int	count;
	int	i;

	count = 0;
	i = start_idx;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

int	get_max_line_length(char **lines, int start_idx)
{
	int	max_len;
	int	current_len;
	int	i;

	max_len = 0;
	i = start_idx;
	while (lines[i])
	{
		current_len = ft_strlen(lines[i]);
		if (current_len > max_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

char	*pad_line_with_spaces(char *line, int target_width)
{
	char	*padded;
	int		line_len;
	int		i;

	line_len = ft_strlen(line);
	padded = malloc(target_width + 1);
	if (!padded)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		padded[i] = line[i];
		i++;
	}
	while (i < target_width)
	{
		padded[i] = ' ';
		i++;
	}
	padded[target_width] = '\0';
	return (padded);
}

int	parse_map_array(char **lines, int start_idx, t_game *game)
{
	int	map_height;
	int	i;
	int	line_idx;

	map_height = count_map_lines(lines, start_idx);
	if (map_height == 0)
		return (0);
	game->map_width = get_max_line_length(lines, start_idx);
	game->map_height = map_height;
	game->map = malloc(sizeof(char *) * (map_height + 1));
	if (!game->map)
		return (0);
	i = 0;
	line_idx = start_idx;
	while (i < map_height && lines[line_idx])
	{
		if (ft_strlen(lines[line_idx]) == 0)
		{
			line_idx++;
			continue ;
		}
		game->map[i] = pad_line_with_spaces(lines[line_idx], game->map_width);
		if (!game->map[i])
			return (0);
		i++;
		line_idx++;
	}
	game->map[i] = NULL;
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
				player_count++;
				game->player_x = j;
				game->player_y = i;
				game->player_dir = game->map[i][j];
			}
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

void	print_final_result(t_game *game)
{
	int	i;

	printf("\n=== PARSING SUCCESSFUL ===\n");
	printf("File: %s\n", game->file_name);
	printf("North texture: %s\n", game->north_texture);
	printf("South texture: %s\n", game->south_texture);
	printf("West texture: %s\n", game->west_texture);
	printf("East texture: %s\n", game->east_texture);
	printf("Floor color: R:%d G:%d B:%d\n",
			game->floor_color[0],
			game->floor_color[1],
			game->floor_color[2]);
	printf("Ceiling color: R:%d G:%d B:%d\n",
			game->ceiling_color[0],
			game->ceiling_color[1],
			game->ceiling_color[2]);
	printf("Map size: %dx%d\n", game->map_width, game->map_height);
	printf("Player position: (%d,%d) facing %c\n",
			game->player_x,
			game->player_y,
			game->player_dir);
	printf("\nMap:\n");
	i = 0;
	while (i < game->map_height)
	{
		printf("%s\n", game->map[i]);
		i++;
	}
	printf("\n=== All validations passed! Ready for raycasting! ===\n");
}
