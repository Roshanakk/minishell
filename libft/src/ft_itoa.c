/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:42:24 by rraffi-k          #+#    #+#             */
/*   Updated: 2022/11/30 11:25:33 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n / 10 != 0)
	{
		i++;
		n = (n - n % 10) / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_size(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	if (n < 0)
		res = -n;
	else
		res = n;
	while (len > 0)
	{
		str[len - 1] = res % 10 + '0';
		res = (res - res % 10) / 10;
		len--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
/*
int main()
{
	int	n = 214748364;
	printf("%s", ft_itoa(n));
	return (0);
}
*/