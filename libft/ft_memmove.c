/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:01:03 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/14 04:48:29 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*sr;
	char	*de;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	de = (char *)dest;
	sr = (char *)src;
	if (de > sr)
	{
		i = n;
		while (i > 0)
		{
			de[i - 1] = sr[i - 1];
			i--;
		}
	}
	else
	{
		ft_memcpy(de, sr, n);
	}
	return (dest);
}
