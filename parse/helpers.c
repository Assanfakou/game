/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:16:22 by lzari             #+#    #+#             */
/*   Updated: 2025/10/20 19:16:23 by lzari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	count_lines(char *content)
{
	int	count;
	int	i;

	if (!content)
		return (0);
	count = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && content[i - 1] != '\n')
		count++;
	return (count);
}

int	copy_line(char *content, char **lines, int line_idx, int *i)
{
	int	j;
	int	start;

	start = *i;
	while (content[*i] && content[*i] != '\n')
		(*i)++;
	lines[line_idx] = malloc(*i - start + 1);
	if (!lines[line_idx])
		return (0);
	j = 0;
	while (start + j < *i)
	{
		lines[line_idx][j] = content[start + j];
		j++;
	}
	lines[line_idx][j] = '\0';
	if (content[*i] == '\n')
		(*i)++;
	return (1);
}

char	**free_and_return_null(char **lines, int line_idx)
{
	while (line_idx > 0)
		free(lines[--line_idx]);
	free(lines);
	return (NULL);
}

char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	start = str;
	while (ft_isspace(*start))
		start++;
	if (*start == '\0')
		return (ft_strdup(""));
	end = str + ft_strlen(str) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = start[i];
	result[i] = '\0';
	return (result);
}
