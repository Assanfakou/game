/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_file_ops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:49:20 by lzari             #+#    #+#             */
/*   Updated: 2025/10/03 09:49:21 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	validate_texture_file(char *path)
{
	int	fd;

	if (!path || ft_strlen(path) == 0)
	{
		printf("Error: Empty texture path\n");
		return (0);
	}
	if (!validate_texture_extension(path))
	{
		printf("Error: Texture must be .xpm file: %s\n", path);
		return (0);
	}
	if (is_directory(path))
	{
		printf("Error: Texture path is a directory: %s\n", path);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Texture file not found: %s\n", path);
		return (0);
	}
	close(fd);
	return (1);
}

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
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = start[i];
		i++;
	}
	result[i] = '\0';
	i = len - 1;
	while (i >= 0 && ft_isspace(result[i]))
	{
		result[i] = '\0';
		i--;
	}
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

int	parse_texture_line(char *line, t_game *game)
{
	char	*trimmed;
	char	*path;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	if (!check_duplicate_texture(game, trimmed))
	{
		free(trimmed);
		return (0);
	}
	path = get_texture_path(trimmed);
	if (!path)
	{
		printf("Error: Missing texture path\n");
		free(trimmed);
		return (0);
	}
	if (!check_extra_content(trimmed, path))
	{
		free(path);
		free(trimmed);
		return (0);
	}
	if (!validate_texture_file(path))
	{
		free(path);
		free(trimmed);
		return (0);
	}
	assign_texture(game, trimmed, path);
	free(trimmed);
	return (1);
}
