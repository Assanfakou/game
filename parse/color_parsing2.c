/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:09:54 by lzari             #+#    #+#             */
/*   Updated: 2025/10/20 17:09:55 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_rgb_components(char *color_str, int *rgb)
{
	int	pos;
	int	i;
	int	value;

	pos = 0;
	i = 0;
	while (i < 3)
	{
		if (!parse_one_rgb_component(color_str, &pos, &value))
			return (0);
		rgb[i] = value;
		if (i < 2)
		{
			if (color_str[pos] != ',')
				return (0);
			pos++;
		}
		i++;
	}
	while (color_str[pos] && ft_isspace(color_str[pos]))
		pos++;
	if (color_str[pos] == '\0')
		return (1);
	return (0);
}

int	parse_colors_values(char *color_str, int *rgb)
{
	char	*trimmed;
	int		result;

	if (!color_str)
		return (0);
	trimmed = trim_whitespace(color_str);
	if (!trimmed)
		return (0);
	if (count_commas(trimmed) != 2)
	{
		free(trimmed);
		return (0);
	}
	result = parse_rgb_components(trimmed, rgb);
	free(trimmed);
	return (result);
}

int	check_duplicate_color(t_game *game, char *trimmed)
{
	if (ft_strncmp(trimmed, "F", 1) == 0 && game->floor_color[0] != -1)
	{
		printf("Error: Duplicate floor color\n");
		return (0);
	}
	if (ft_strncmp(trimmed, "C", 1) == 0 && game->ceiling_color[0] != -1)
	{
		printf("Error: Duplicate ceiling color\n");
		return (0);
	}
	return (1);
}
