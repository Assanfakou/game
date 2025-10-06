/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:48:38 by lzari             #+#    #+#             */
/*   Updated: 2025/10/03 09:48:41 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	validate_extension(char *file_name)
{
	int	len;

	if (!file_name)
		return (0);
	len = ft_strlen(file_name);
	if (len < 5)
		return (0);
	if (ft_strncmp(file_name + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	is_directory(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

int	file_exists_and_readable(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open file '%s': %s\n", file_name,
				strerror(errno));
		return (0);
	}
	close(fd);
	return (1);
}

int	valid_argument(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Invalid number of arguments");
		return (0);
	}
	if (!argv[1])
	{
		print_error("Invalid argument: NULL file path");
		return (0);
	}
	if (is_directory(argv[1]))
	{
		print_error("Argument is a directory, not a file");
		return (0);
	}
	if (!file_exists_and_readable(argv[1]))
		return (0);
	if (!validate_extension(argv[1]))
	{
		print_error("Invalid file extension. Use .cub files only");
		return (0);
	}
	return (1);
}

void	print_parsed_elements(t_game *game)
{
	printf("\n=== PARSED ELEMENTS ===\n");

	if (game->north_texture)
		printf("North texture: %s\n", game->north_texture);
	else
		printf("North texture: NULL\n");

	if (game->south_texture)
		printf("South texture: %s\n", game->south_texture);
	else
		printf("South texture: NULL\n");

	if (game->west_texture)
		printf("West texture: %s\n", game->west_texture);
	else
		printf("West texture: NULL\n");

	if (game->east_texture)
		printf("East texture: %s\n", game->east_texture);
	else
		printf("East texture: NULL\n");

	printf("Floor color: R:%d G:%d B:%d\n",
		game->floor_color[0],
		game->floor_color[1],
		game->floor_color[2]);

	printf("Ceiling color: R:%d G:%d B:%d\n",
		game->ceiling_color[0],
		game->ceiling_color[1],
		game->ceiling_color[2]);

	printf("========================\n\n");
}

int	main(int argc, char **argv)
{
	t_game	game;
	char	*file_content;
	char	**lines;
	int		line_count;
	int		map_start;

	if (!valid_argument(argc, argv))
		return (1);
	init_game_struct(&game, argv[1]);
	file_content = read_entire_file(argv[1]);
	if (!file_content)
	{
		print_error("Failed to read file");
		free_game_struct(&game);
		return (1);
	}
	line_count = count_lines(file_content);
	if (line_count == 0)
	{
		print_error("Empty file");
		free(file_content);
		free_game_struct(&game);
		return (1);
	}
	lines = split_lines(file_content, line_count);
	if (!lines)
	{
		print_error("Failed to split file content");
		free(file_content);
		free_game_struct(&game);
		return (1);
	}
	map_start = parse_elements(lines, &game);
	printf("DEBUG: map_start returned = %d\n", map_start);
	if (map_start == 0)
	{
		printf("Error: Failed to parse elements (textures/colors)\n");
		free(file_content);
		free_string_array(lines);
		free_game_struct(&game);
		return (1);
	}

	printf("\n=== PARSED ELEMENTS ===\n");

	if (game.north_texture)
		printf("North texture: %s\n", game.north_texture);
	else
		printf("North texture: NULL\n");

	if (game.south_texture)
		printf("South texture: %s\n", game.south_texture);
	else
		printf("South texture: NULL\n");

	if (game.west_texture)
		printf("West texture: %s\n", game.west_texture);
	else
		printf("West texture: NULL\n");

	if (game.east_texture)
		printf("East texture: %s\n", game.east_texture);
	else
		printf("East texture: NULL\n");

	printf("Floor color: R:%d G:%d B:%d\n",
		game.floor_color[0],
		game.floor_color[1],
		game.floor_color[2]);

	printf("Ceiling color: R:%d G:%d B:%d\n",
		game.ceiling_color[0],
		game.ceiling_color[1],
		game.ceiling_color[2]);

	printf("========================\n\n");

	printf("DEBUG: Starting map parsing at line %d\n", map_start);
	if (!parse_map(lines, map_start, &game))
	{
		printf("Error: Map parsing failed\n");
		free(file_content);
		free_string_array(lines);
		free_game_struct(&game);
		return (1);
	}
	print_final_result(&game);
	free(file_content);
	free_string_array(lines);
	free_game_struct(&game);
	return (0);
}
