/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:49:01 by lzari             #+#    #+#             */
/*   Updated: 2025/10/03 09:49:03 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*get_color_part(char *trimmed)
{
	int	i;

	i = 0;
	while (trimmed[i] && !ft_isspace(trimmed[i]))
		i++;
	while (trimmed[i] && ft_isspace(trimmed[i]))
		i++;
	return (trim_whitespace(trimmed + i));
}

static int	assign_color(char *trimmed, char *color_part, t_game *game)
{
	if (!check_duplicate_color(game, trimmed))
		return (0);
	if (ft_strncmp(trimmed, "F", 1) == 0)
	{
		if (!parse_colors_values(color_part, game->floor_color))
		{
			printf("Error: Invalid color format - must be R,G,B\n");
			return (0);
		}
	}
	else if (ft_strncmp(trimmed, "C", 1) == 0)
	{
		if (!parse_colors_values(color_part, game->ceiling_color))
		{
			printf("Error: Invalid color format - must be R,G,B\n");
			return (0);
		}
	}
	return (1);
}

int	parse_color_line(char *line, t_game *game)
{
	char	*trimmed;
	char	*color_part;
	int		result;

	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	color_part = get_color_part(trimmed);
	if (!color_part)
	{
		free(trimmed);
		return (0);
	}
	result = assign_color(trimmed, color_part, game);
	free(color_part);
	free(trimmed);
	return (result);
}

static int	process_line(char *line, t_game *game, int *elements_found)
{
	if (is_texture_line(line))
	{
		if (!parse_texture_line(line, game))
			return (0);
		(*elements_found)++;
	}
	else if (is_color_line(line))
	{
		if (!parse_color_line(line, game))
			return (0);
		(*elements_found)++;
	}
	else
	{
		printf("Error: Invalid line format: '%s'\n", line);
		return (0);
	}
	return (1);
}

int	parse_elements(char **lines, t_game *game)
{
	int	i;
	int	elements_found;

	i = 0;
	elements_found = 0;
	while (lines[i] && elements_found < 6)
	{
		if (ft_strlen(lines[i]) != 0)
		{
			if (!is_texture_line(lines[i]) && !is_color_line(lines[i]))
				break ;
			if (!process_line(lines[i], game, &elements_found))
				return (0);
		}
		i++;
	}
	if (elements_found != 6)
	{
		printf("Error: Missing elements (found %d/6)\n", elements_found);
		return (0);
	}
	while (lines[i] && ft_strlen(lines[i]) == 0)
		i++;
	return (i);
}
