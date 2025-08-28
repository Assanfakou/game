/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:47:13 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/14 07:24:51 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*st;
	size_t	i;

	st = (char *)s;
	i = 0;
	while (i < n)
	{
		if (st[i] == (char)c)
		{
			return (&st[i]);
		}
		i++;
	}
	return (NULL);
}
