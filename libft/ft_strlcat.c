/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:20:36 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/13 02:23:27 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	d_length;
	size_t	s_length;

	s_length = 0;
	while (src[s_length])
		s_length++;
	if (size == 0)
		return (s_length);
	d_length = 0;
	while (dest[d_length])
		d_length++;
	if (d_length >= size)
		return (size + s_length);
	j = d_length;
	i = 0;
	while (src[i] && j < (size - 1))
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (d_length + s_length);
}
