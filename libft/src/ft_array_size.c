/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:25:29 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/19 19:58:17 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_array_size(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

// int main(int argc, char **argv)
// {
// 	int i = 0;
// 	while (argv[i])
// 	{
// 		printf("%s ; ", argv[i]);
// 		i++;
// 	}
// 	printf("nb = %zu\n", ft_array_size(argv));
// }