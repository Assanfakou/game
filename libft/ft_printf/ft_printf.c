/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:36:51 by hfakou            #+#    #+#             */
/*   Updated: 2024/12/08 17:57:15 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *firstpar, ...)
{
	int		i;
	int		vas;
	va_list	arg;

	va_start(arg, firstpar);
	i = 0;
	vas = 0;
	if (firstpar == NULL)
		return (-1);
	while (firstpar[i] != '\0')
	{
		if (firstpar[i] == '%')
		{
			if (firstpar[i + 1] != '\0')
			{
				vas += ft_checker(arg, firstpar[i + 1]);
				i++;
			}
		}
		else
			vas += ft_putchar(firstpar[i]);
		i++;
		va_end(arg);
	}
	return (vas);
}
