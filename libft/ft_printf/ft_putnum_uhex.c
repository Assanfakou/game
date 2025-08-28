/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnum_uhex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:41:16 by hfakou            #+#    #+#             */
/*   Updated: 2024/12/08 16:38:11 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnum_uhex(unsigned int nbr)
{
	int		r;
	char	*bas;

	bas = "0123456789ABCDEF";
	r = 0;
	if (nbr >= 16)
		r = ft_putnum_uhex(nbr / 16);
	r += ft_putchar(bas[nbr % 16]);
	return (r);
}
