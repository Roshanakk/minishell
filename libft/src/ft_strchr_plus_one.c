/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:51:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/19 16:12:36 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_plus_one(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c && s[i + 1])
			return ((char *)(s + i + 1));
		i++;
	}
	if (s[i] == c && s[i + 1])
		return ((char *)(s + i + 1));
	return (NULL);
}

/*
int main()
{
	printf("%s", ft_strchr("aslat", 's'));
	return (0);
}
*/