/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:10:56 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/04 16:11:50 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned int	i;
	char			ct;

	ct = (char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == ct)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (str[i] == ct)
		return ((char *)&str[i]);
	return (NULL);
}
