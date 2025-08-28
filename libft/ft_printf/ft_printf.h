/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:37:54 by hfakou            #+#    #+#             */
/*   Updated: 2024/12/08 18:24:41 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <unistd.h>

int	ft_putnbr(int n);
int	ft_putstr(char *st);
int	ft_putchar(char c);
int	ft_putnum_uhex(unsigned int nbr);
int	ft_putnum_lhex(unsigned int nb);
int	ft_uuputnb(unsigned int nbs);
int	ft_putaddr(unsigned long add);
int	ft_putaddress_with_handle(unsigned long adde);
int	ft_checker(va_list arg, char s);
int	ft_printf(const char *firstpar, ...);

#endif
