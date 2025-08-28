/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:15:08 by hfakou            #+#    #+#             */
/*   Updated: 2025/03/07 01:54:27 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	d;
	char	*dest_str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	dest_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dest_str == NULL)
		return (NULL);
	i = 0;
	d = 0;
	while (s1[d])
		dest_str[i++] = s1[d++];
	d = 0;
	while (s2[d])
		dest_str[i++] = s2[d++];
	dest_str[i] = '\0';
	return (dest_str);
}
