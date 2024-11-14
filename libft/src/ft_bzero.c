/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:49:04 by rraffi-k          #+#    #+#             */
/*   Updated: 2022/12/01 17:26:04 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

/*
int main()
{
	int str[] = {1, 2, 3, 4};
	ft_bzero(str, 3);
	//bzero(str, 3);
	printf("%d %d %d %d", str[0], str[1], str[2], str[3]);
	return (0);
}
*/