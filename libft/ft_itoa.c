/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:42:06 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/04 15:44:43 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	dig_len(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
		i = 1;
	while (nb)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

static void	fill_str(char *dest, long nbr, int len)
{
	dest[len] = '\0';
	if (nbr == 0)
	{
		dest[0] = '0';
		return ;
	}
	while (nbr)
	{
		dest[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	i;

	i = n;
	len = dig_len(i);
	if (n < 0)
		i *= -1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	fill_str(str, i, len);
	return (str);
}
