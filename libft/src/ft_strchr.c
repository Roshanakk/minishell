/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:43:20 by balacam           #+#    #+#             */
/*   Updated: 2022/12/01 18:34:31 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
	strchr(): 
	Function returns a pointer to the first 
	occurrence of the character c in the string s.
*/

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (c < 0)
		return (0);
	i = 0;
	while (s[i] && (char)s[i] != (char)c)
		i++;
	if ((char)s[i] == (char)c)
		return ((char *)s + i);
	else
		return (NULL);
}
/*
int main()
{
	const char str[] = "bonjour.hello";
	const char ch = 'b';
	char *ret;
	char *ret2;

	ret = strchr(str, ch);
	ret2 = ft_strchr(str, ch);
	printf("%s\n", ret);
	printf("%s", ret2);

	return(0);
}
*/
