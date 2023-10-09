/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:16:02 by rraffi-k          #+#    #+#             */
/*   Updated: 2022/12/14 14:58:32 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pointer(char c, va_list args, int *nbr)
{
	void	*cur_arg;

	if (c == 's')
	{
		cur_arg = va_arg(args, char *);
		if (!cur_arg)
			ft_putstr("(null)", nbr);
		else
			ft_putstr(cur_arg, nbr);
	}
	else if (c == 'p')
	{
		cur_arg = va_arg(args, void *);
		if (!cur_arg)
			ft_putstr("(nil)", nbr);
		else
		{
			ft_putstr("0x", nbr);
			ft_putnbr_base_long((unsigned long)cur_arg, nbr);
		}
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_bis(const char *s, int start, int end, int *nbr)
{
	int	i;

	i = start;
	if (!s)
		return ;
	while (s[i] != '\0' && i < end)
	{
		write(1, &s[i], 1);
		i++;
		(*nbr)++;
	}
}

void	ft_putstr(char *s, int *nbr)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
		(*nbr)++;
	}
}

void	ft_intochar(int a, int *nbr)
{
	char	z;

	z = a;
	write(1, &z, 1);
	(*nbr)++;
}
