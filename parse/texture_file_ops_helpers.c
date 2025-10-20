/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_file_ops_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 22:10:41 by lzari             #+#    #+#             */
/*   Updated: 2025/10/20 22:10:42 by lzari            ###   ########.fr       */
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

char	*extract_path_string(char *start, int len)
{
	char	*result;
	int		i;

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
	return (result);
}

void	trim_trailing_spaces(char *result)
{
	int	i;
	int	len;

	len = ft_strlen(result);
	i = len - 1;
	while (i >= 0 && ft_isspace(result[i]))
	{
		result[i] = '\0';
		i--;
	}
}
