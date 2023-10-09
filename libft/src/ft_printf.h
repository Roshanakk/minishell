/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:18:47 by rraffi-k          #+#    #+#             */
/*   Updated: 2022/12/15 11:31:41 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *arg0, ...);
void	ft_case(char c, va_list args, int *nbr);
void	ft_putstr_bis(const char *s, int start, int end, int *nbr);
void	ft_putchar(char c, int *nbr);
void	ft_putnbr(int n, int *nbr);
void	ft_putnbr_u(unsigned int n, int	*nbr);
size_t	ft_strlen(const char *s);
void	ft_putstr(char *s, int *nbr);
void	ft_putnbr_base_long(unsigned long long nb, int *nbr);
void	ft_putnbr_base(unsigned int nb, char c, int *nbr);
void	ft_intochar(int a, int *nbr);
void	ft_pointer(char c, va_list args, int *nbr);

#endif