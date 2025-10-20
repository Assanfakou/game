/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_file_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assankou <assankou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:49:20 by lzari             #+#    #+#             */
/*   Updated: 2025/10/06 15:57:46 by assankou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*get_texture_path(char *trimmed)
{
	int		i;
	char	*start;
	char	*result;
	int		len;

	i = 0;
	while (trimmed[i] && !ft_isspace(trimmed[i]))
		i++;
	while (trimmed[i] && ft_isspace(trimmed[i]))
		i++;
	start = trimmed + i;
	len = ft_strlen(start);
	if (len == 0)
		return (NULL);
	result = extract_path_string(start, len);
	if (!result)
		return (NULL);
	trim_trailing_spaces(result);
	return (result);
}

static void	assign_texture(t_game *game, char *trimmed, char *path)
{
	if (ft_strncmp(trimmed, "NO", 2) == 0)
		game->north_texture = path;
	else if (ft_strncmp(trimmed, "SO", 2) == 0)
		game->south_texture = path;
	else if (ft_strncmp(trimmed, "WE", 2) == 0)
		game->west_texture = path;
	else if (ft_strncmp(trimmed, "EA", 2) == 0)
		game->east_texture = path;
}

static int	validate_path_and_file(char *trimmed, char *path)
{
	if (!check_extra_content(trimmed, path))
	{
		free(path);
		return (0);
	}
	if (!validate_texture_file(path))
	{
		free(path);
		return (0);
	}
	return (1);
}

static int	process_texture_path(char *trimmed, t_game *game)
{
	char	*path;

	path = get_texture_path(trimmed);
	if (!path)
	{
		printf("Error: Missing texture path\n");
		return (0);
	}
	if (!validate_path_and_file(trimmed, path))
		return (0);
	assign_texture(game, trimmed, path);
	return (1);
}

int	parse_texture_line(char *line, t_game *game)
{
	char	*trimmed;
	int		result;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	if (!check_duplicate_texture(game, trimmed))
	{
		free(trimmed);
		return (0);
	}
	result = process_texture_path(trimmed, game);
	free(trimmed);
	return (result);
}
