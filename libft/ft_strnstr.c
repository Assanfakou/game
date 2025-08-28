/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:27:55 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/14 08:35:09 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l;
	size_t	g;
	size_t	i;

	if (!big || !little)
		return (NULL);
	if (*little == '\0')
		return ((char *)(big));
	l = 0;
	while (big[l] != '\0' && l < len)
	{
		i = l;
		g = 0;
		while (little[g] != '\0' && i < len && big[i] != '\0'
			&& big[i] == little[g])
		{
			g++;
			i++;
		}
		if (little[g] == 0)
			return ((char *)(&big[l]));
		l++;
	}
	return (NULL);
}
