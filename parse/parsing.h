/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 09:49:52 by lzari             #+#    #+#             */
/*   Updated: 2025/10/03 09:49:53 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 1024

typedef struct s_game
{
	char	*file_name;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		textures_parsed;
	int		colors_parsed;
}			t_game;

char		*ft_strdup(const char *s);

char		*read_entire_file(char *filename);
int			count_lines(char *content);
char		**split_lines(char *content, int line_count);

void		init_game_struct(t_game *game, char *filename);
void		free_string_array(char **array);
void		free_game_struct(t_game *game);

int			ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *str);
int			ft_isspace(char c);
int			ft_isdigit(char c);
char		*ft_strdup(const char *s);
char		*trim_whitespace(char *str);

int			is_texture_line(char *line);
int			is_color_line(char *line);

int			check_duplicate_texture(t_game *game, char *trimmed);
int			validate_texture_extension(char *path);
int			check_extra_content(char *trimmed, char *path);

int			validate_texture_file(char *path);
int			parse_texture_line(char *line, t_game *game);

int			parse_colors_values(char *color_str, int *rgb);
int			parse_color_line(char *line, t_game *game);

int			parse_elements(char **lines, t_game *game);

int			valid_argument(int argc, char **argv);
int			validate_extension(char *file_name);
int			is_directory(char *path);
int			file_exists_and_readable(char *file_name);

void		print_error(char *msg);

int			parse_map(char **lines, int start_idx, t_game *game);
void		print_final_result(t_game *game);

int			is_valid_map_char(char c);
int			is_player_char(char c);

#endif
