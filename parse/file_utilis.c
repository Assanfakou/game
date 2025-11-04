/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utilis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <lzari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:32:40 by lzari             #+#    #+#             */
/*   Updated: 2025/11/03 11:57:01 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*append_buffer(char *content, char *buffer, int bytes_read, int total)
{
	char	*temp;
	int		i;
	int		j;

	temp = malloc(total + bytes_read + 1);
	if (!temp)
	{
		free(content);
		return (NULL);
	}
	i = 0;
	while (i < total)
	{
		temp[i] = content[i];
		i++;
	}
	j = 0;
	while (j < bytes_read)
	{
		temp[total + j] = buffer[j];
		j++;
	}
	temp[total + bytes_read] = '\0';
	free(content);
	return (temp);
}

static char	*read_file_loop(int fd, char *content, int *total)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			content = append_buffer(content, buffer, bytes_read, *total);
			if (!content)
				return (NULL);
			*total += bytes_read;
		}
	}
	return (content);
}

char	*read_entire_file(char *filename)
{
	int		fd;
	char	*content;
	int		total_size;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = malloc(1);
	if (!content)
		return (NULL);
	content[0] = '\0';
	total_size = 0;
	content = read_file_loop(fd, content, &total_size);
	close(fd);
	if (!content)
		return (NULL);
	return (content);
}

char	**split_lines(char *content, int line_count)
{
	char	**lines;
	int		i;
	int		line_idx;

	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	line_idx = 0;
	while (content[i] && line_idx < line_count)
	{
		if (!copy_line(content, lines, line_idx, &i))
			return (free_and_return_null(lines, line_idx));
		line_idx++;
	}
	lines[line_idx] = NULL;
	return (lines);
}
