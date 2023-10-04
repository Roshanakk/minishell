/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:48:34 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/04 10:30:36 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testshell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	if (!s2)
		return ((char *)s1);
	if (!s1)
		return ((char *)s2);
	string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!string)
		return (0);
	i = 0;
	while (((char *)s1)[i])
	{
		string[i] = ((char *)s1)[i];
		i++;
	}
	j = 0;
	while (((char *)s2)[j])
	{
		string[i + j] = ((char *)s2)[j];
		j++;
	}
	string[i + j] = '\0';
	return (string);
}

// int main()
// {
// 	char s1[] = "where is my ";
// 	char s2[] = "zzzz";
// 	printf("%s", ft_strjoin(s1, NULL));
// 	return (0);
// }
