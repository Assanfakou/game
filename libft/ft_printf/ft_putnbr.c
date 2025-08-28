/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:40:27 by hfakou            #+#    #+#             */
/*   Updated: 2024/12/08 18:21:44 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nbs)
{
	unsigned int	s;
	int				se;

	se = 0;
	if (nbs < 0)
	{
		se += ft_putchar('-');
		s = -nbs;
	}
	else
		s = nbs;
	if (s > 9)
		se += ft_putnbr(s / 10);
	se += ft_putchar((s % 10) + '0');
	return (se);
}
