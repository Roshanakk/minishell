/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 15:10:12 by rraffi-k          #+#    #+#             */
/*   Updated: 2022/12/15 12:16:49 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base_long(unsigned long long nb, int *nbr)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb == 0)
		ft_putchar(base[0], nbr);
	if (nb < 16)
		ft_putchar(base[nb], nbr);
	else
	{
		ft_putnbr_base_long(nb / 16, nbr);
		ft_putchar(base[nb % 16], nbr);
	}
}

void	ft_putnbr_base(unsigned int nb, char c, int *nbr)
{
	char	*base;

	if (c == 'x')
		base = "0123456789abcdef";
	else if (c == 'X')
		base = "0123456789ABCDEF";
	if (nb < 16)
		ft_putchar(base[nb], nbr);
	else
	{
		ft_putnbr_base(nb / 16, c, nbr);
		ft_putchar(base[nb % 16], nbr);
	}
}
