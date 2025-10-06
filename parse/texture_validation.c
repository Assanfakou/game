/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:49:31 by lzari             #+#    #+#             */
/*   Updated: 2025/10/03 09:49:32 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_texture_line(char *line)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0 || ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0 || ft_strncmp(trimmed, "EA ",
			3) == 0)
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

int	is_color_line(char *line)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "F ", 2) == 0 || ft_strncmp(trimmed, "C ", 2) == 0)
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

int	check_duplicate_texture(t_game *game, char *trimmed)
{
	if (ft_strncmp(trimmed, "NO", 2) == 0 && game->north_texture)
	{
		printf("Error: Duplicate north texture\n");
		return (0);
	}
	if (ft_strncmp(trimmed, "SO", 2) == 0 && game->south_texture)
	{
		printf("Error: Duplicate south texture\n");
		return (0);
	}
	if (ft_strncmp(trimmed, "WE", 2) == 0 && game->west_texture)
	{
		printf("Error: Duplicate west texture\n");
		return (0);
	}
	if (ft_strncmp(trimmed, "EA", 2) == 0 && game->east_texture)
	{
		printf("Error: Duplicate east texture\n");
		return (0);
	}
	return (1);
}

int	validate_texture_extension(char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	return (1);
}

int	check_extra_content(char *trimmed, char *path)
{
	int	expected_len;
	int	actual_len;

	expected_len = 2 + 1 + ft_strlen(path);
	actual_len = ft_strlen(trimmed);
	if (actual_len > expected_len)
	{
		printf("Error: Extra content after texture path\n");
		return (0);
	}
	return (1);
}
