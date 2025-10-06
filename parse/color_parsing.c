/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:48:05 by lzari             #+#    #+#             */
/*   Updated: 2025/10/03 09:48:07 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_isdigit_str(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static char	*extract_number(char *str, int *pos)
{
	char	*result;
	int		start;
	int		len;
	int		i;

	while (str[*pos] && ft_isspace(str[*pos]))
		(*pos)++;
	start = *pos;
	while (str[*pos] && str[*pos] >= '0' && str[*pos] <= '9')
		(*pos)++;
	len = *pos - start;
	if (len == 0)
		return (NULL);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = str[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	validate_rgb_component(char *component)
{
	int	value;

	if (!ft_isdigit_str(component))
		return (-1);
	value = ft_atoi(component);
	if (value < 0 || value > 255)
		return (-1);
	return (value);
}

static int	parse_rgb_components(char *color_str, int *rgb)
{
	int		pos;
	int		i;
	char	*component;
	int		value;

	pos = 0;
	i = 0;
	while (i < 3)
	{
		component = extract_number(color_str, &pos);
		if (!component)
			return (0);
		value = validate_rgb_component(component);
		free(component);
		if (value == -1)
			return (0);
		rgb[i] = value;
		while (color_str[pos] && ft_isspace(color_str[pos]))
			pos++;
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
