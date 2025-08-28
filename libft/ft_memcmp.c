/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:49:07 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/04 15:50:18 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*st;
	unsigned char	*sd;

	st = (unsigned char *)s1;
	sd = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (st[i] == sd[i])
		{
			i++;
		}
		else
		{
			return (st[i] - sd[i]);
		}
	}
	return (0);
}
