/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:48:17 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/09 17:08:57 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strcpy(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(src);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/*
int main()
{
	char dst1[] = "Yo";
	char src1[100] = "AuRevoir";

	//char dst2[] = "Bonjour";
	//char src2[100] = "AuRevoir";

	//printf("%ld\n", ft_strlen(src1));
	printf("%ld %s\n", ft_strlcpy(dst1, src1, 20), dst1);
	//printf("%ld %s\n", ft_strlcpy(dst2, src2, 10), dst2);
	return (0);
}
*/