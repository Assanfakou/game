/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 22:28:48 by hfakou            #+#    #+#             */
/*   Updated: 2024/12/28 11:09:08 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_calloc(size_t chunk, size_t size)
{
	char	*south;
	size_t	i;
	size_t	total;

	if (chunk == 0 || size == 0)
		return (malloc(0));
	if (chunk > SIZE_MAX / size)
		return (NULL);
	total = chunk * size;
	south = malloc(total);
	if (!south)
		return (NULL);
	i = 0;
	while (i < total)
	{
		south[i] = '\0';
		i++;
	}
	return (south);
}

char	*extract_then_update(char **static_buffer)
{
	char	*line;
	char	*new_line_pos;
	char	*cache;

	if (!*static_buffer)
		return (NULL);
	new_line_pos = ft_strchr(*static_buffer, '\n');
	if (new_line_pos)
	{
		line = ft_strdup_nln(*static_buffer);
		if (*(new_line_pos + 1) != '\0')
		{
			cache = ft_strdup(new_line_pos + 1);
			free(*static_buffer);
			*static_buffer = cache;
		}
		else
		{
			free(*static_buffer);
			*static_buffer = NULL;
		}
		return (line);
	}
	return (NULL);
}

char	*read_result(ssize_t bytes_read, char **static_buf, char **read_buf)
{
	char	*temp;

	if (bytes_read < 0)
	{
		free(*static_buf);
		free(*read_buf);
		*static_buf = NULL;
		return (NULL);
	}
	if (bytes_read == 0)
	{
		free(*read_buf);
		temp = ft_strdup(*static_buf);
		free(*static_buf);
		*static_buf = NULL;
		return (temp);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	ssize_t		bytes_read;
	char		*buffer;
	char		*line;
	char		*temp_buffer;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = ft_calloc((size_t)(BUFFER_SIZE + 1), 1);
	while (buffer)
	{
		line = extract_then_update(&static_buffer);
		if (line)
			return (free(buffer), line);
		else
			(free(buffer), buffer = ft_calloc((size_t)BUFFER_SIZE + 1, 1));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (read_result(bytes_read, &static_buffer, &buffer));
		temp_buffer = ft_strjoin(static_buffer, buffer);
		free(static_buffer);
		static_buffer = temp_buffer;
	}
	return (NULL);
}
