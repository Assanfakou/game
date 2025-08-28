/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:38:25 by hfakou            #+#    #+#             */
/*   Updated: 2024/12/08 18:23:58 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putaddress_with_handle(unsigned long adde)
{
	int		re;

	re = 0;
	if (adde == 0)
		return (write(1, "(nil)", 5));
	re += write(1, "0x", 2);
	re += ft_putaddr(adde);
	return (re);
}

int	ft_putaddr(unsigned long add)
{
	int		re;
	char	*base;

	re = 0;
	base = "0123456789abcdef";
	if (add >= 16)
		re += ft_putaddr(add / 16);
	re += ft_putchar(base[add % 16]);
	return (re);
}
