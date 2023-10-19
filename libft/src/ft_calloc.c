/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:01:37 by rraffi-k          #+#    #+#             */
/*   Updated: 2022/12/08 14:55:26 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	char	*res;

	if (!nmemb || !size)
	{
		res = malloc(1);
		return (res);
	}
	if (nmemb * size / size != nmemb)
		return (NULL);
	str = (char *)malloc(size * nmemb);
	if (!str)
		return (NULL);
	ft_bzero(str, size * nmemb);
	return (str);
}

// int main()
// {
// 	char *s = ft_calloc(5, 0);
// 	printf("%d %d %d %d %d", s[0], s[1], s[2], s[3], s[4]);
// 	printf("%ld", SIZE_MAX);
// 	printf("\n");
// 	free(s);
// 	return (0);
// }
