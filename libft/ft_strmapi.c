/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:23:40 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/14 04:30:18 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res_str;
	size_t			len;

	if (!s)
		return (ft_strdup(""));
	if (!f)
		return (ft_strdup(s));
	len = ft_strlen(s);
	res_str = malloc(sizeof(char) * (len + 1));
	if (!res_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res_str[i] = (f)(i, s[i]);
		i++;
	}
	res_str[i] = '\0';
	return (res_str);
}
