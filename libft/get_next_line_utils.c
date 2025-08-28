/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:00:43 by hfakou            #+#    #+#             */
/*   Updated: 2025/03/07 00:23:18 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_strchr(char *str, char to_find)
// {
// 	int	i;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == to_find)
// 			return (&str[i]);
// 		i++;
// 	}
// 	if (str[i] == to_find)
// 		return (&str[i]);
// 	return (NULL);
// }

// char	*ft_strdup(const char *str)
// {
// 	char	*buffer;
// 	size_t	i;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != '\0')
// 		i++;
// 	buffer = malloc(sizeof(char) * i + 1);
// 	if (buffer == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (str[i])
// 	{
// 		buffer[i] = str[i];
// 		i++;
// 	}
// 	buffer[i] = '\0';
// 	return (buffer);
// }

char	*ft_strdup_nln(const char *str)
{
	char	*buffer;
	size_t	i;
	size_t	j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	buffer = malloc(sizeof(char) * i + 2);
	if (buffer == NULL)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		buffer[j] = str[j];
		j++;
	}
	buffer[j] = '\0';
	return (buffer);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(const char *s1, const char *s2)
// {
// 	char	*final_string;
// 	size_t	i;
// 	size_t	s;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	final_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!final_string)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		final_string[i] = s1[i];
// 		i++;
// 	}
// 	s = 0;
// 	while (s2[s])
// 		final_string[i++] = s2[s++];
// 	final_string[i] = '\0';
// 	return (final_string);
// }

// char *ft_strduptoc(const char *str, char c)
// {
// 	size_t s;
// 	size_t robe;
// 	char *allocated;

// 	if (!str)
// 		return (NULL);
// 	robe = 0;
// 	while (str[robe] && str[robe] != c)
// 		robe++;
// 	if (str[robe] != c)
// 		return (NULL);
//     if (c == '\0')
// 			allocated = malloc(sizeof(char) * (robe + 1));
//     else
// 	{
//         allocated = malloc(sizeof(char) * (robe + 2));
// 		if (allocated == NULL)
// 			return (NULL);
// 	}
// 	s = 0;
// 	while (s <= robe)
// 	{
// 		allocated[s] = str[s];
// 		s++;
// 	}
//     if (c != '\0')
// 			allocated[s] = '\0';
// 	return (allocated);
// }