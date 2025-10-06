/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:48:26 by lzari             #+#    #+#             */
/*   Updated: 2025/10/03 09:48:30 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_game_struct(t_game *game, char *filename)
{
	game->file_name = ft_strdup(filename);
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
	game->floor_color[0] = -1;
	game->floor_color[1] = -1;
	game->floor_color[2] = -1;
	game->ceiling_color[0] = -1;
	game->ceiling_color[1] = -1;
	game->ceiling_color[2] = -1;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_x = -1;
	game->player_y = -1;
	game->player_dir = '\0';
	game->textures_parsed = 0;
	game->colors_parsed = 0;
}

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_game_struct(t_game *game)
{
	if (game->file_name)
		free(game->file_name);
	if (game->north_texture)
		free(game->north_texture);
	if (game->south_texture)
		free(game->south_texture);
	if (game->west_texture)
		free(game->west_texture);
	if (game->east_texture)
		free(game->east_texture);
	if (game->map)
		free_string_array(game->map);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		||c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
