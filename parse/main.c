/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <lzari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:48:38 by lzari             #+#    #+#             */
/*   Updated: 2025/11/04 15:42:42 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	free_resources(t_game *game,
		char *file_content, char **lines, char *msg)
{
	if (lines)
		free_string_array(lines);
	if (file_content)
		free(file_content);
	if (game)
		free_game_struct(game);
	if (msg)
		print_error(msg);
	return (1);
}

static int	parse_lines_and_map(t_game *game,
		char **lines, char *file_content)
{
	int	map_start;

	map_start = parse_elements(lines, game);
	if (map_start == 0 || !parse_map(lines, map_start, game))
		return (free_resources(game,
				file_content,
				lines,
				"Invalid map or elements"));
	free(file_content);
	free_string_array(lines);
	return (0);
}

static int	parse_file_content(t_game *game, char *file_content)
{
	char	**lines;
	int		line_count;

	line_count = count_lines(file_content);
	if (line_count == 0)
		return (free_resources(game,
				file_content,
				NULL,
				"Empty file"));
	lines = split_lines(file_content, line_count);
	if (!lines)
		return (free_resources(game,
				file_content,
				NULL,
				"Failed to split file content"));
	return (parse_lines_and_map(game, lines, file_content));
}

int	get_data(t_game *game, int argc, char **argv)
{
	char	*file_content;

	if (!valid_argument(argc, argv))
		return (1);
	init_game_struct(game, argv[1]);
	file_content = read_entire_file(argv[1]);
	if (!file_content)
	{
		print_error("Failed to read file");
		free_game_struct(game);
		return (1);
	}
	if (parse_file_content(game, file_content))
		return (1);
	return (0);
}
