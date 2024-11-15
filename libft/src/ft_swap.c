/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:04:17 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 12:00:24 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(char **a, char **b)
{
	char	*a1;

	a1 = *a;
	*a = *b;
	*b = a1;
}
