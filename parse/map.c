/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:55:39 by lzari             #+#    #+#             */
/*   Updated: 2025/10/20 16:55:40 by lzari            ###   ########.fr       */
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
