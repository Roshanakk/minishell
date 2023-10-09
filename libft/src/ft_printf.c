/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 16:21:35 by rraffi-k          #+#    #+#             */
/*   Updated: 2022/12/15 12:50:29 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_case(char c, va_list args, int *nbr)
{
	if (!c)
		return ;
	if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), nbr);
	if (c == 'u')
		ft_putnbr_u(va_arg(args, unsigned int), nbr);
	if (c == 'c')
		ft_intochar(va_arg(args, int), nbr);
	if (c == 's' || c == 'p')
		ft_pointer(c, args, nbr);
	if (c == 'x' || c == 'X')
		ft_putnbr_base(va_arg(args, int), c, nbr);
}

int	ft_printf(const char *arg0, ...)
{
	va_list	args;
	int		start;
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	va_start(args, arg0);
	while (arg0[i])
	{
		start = i;
		while (arg0[i] && arg0[i] != '%')
			i++;
		ft_putstr_bis(arg0, start, i, &nbr);
		if (!arg0[i])
			return (nbr);
		else if (arg0[i + 1] == '%')
			ft_putchar('%', &nbr);
		else
			ft_case(arg0[i + 1], args, &nbr);
		i += 2;
	}
	return (nbr);
}

// int main()
// {
// 	// unsigned int b = 4294967295;
// 	// int a = 5;
// 	// int c = -12344;
// 	printf("%d\n", printf(" %%   %%   %% \n"));
// 	ft_printf("%d", ft_printf(" %%   %%   %% \n"));
// 	return (0);
// }