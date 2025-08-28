/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:42:08 by hfakou            #+#    #+#             */
/*   Updated: 2024/12/08 16:38:09 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *st)
{
	int		i;
	int		re;

	re = 0;
	i = 0;
	if (st == NULL)
		return (write (1, "(null)", 6));
	while (st[i])
	{
		re += ft_putchar(st[i]);
		i++;
	}
	return (re);
}
