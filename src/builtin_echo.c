/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:55:03 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/13 11:20:17 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int respects_n_format(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*return la position du premier arg apres l'option -n (ou -nnnn)*/
// int	check_n(char **args)
// {
// 	int	i;

// 	i = 0;
// 	while (args[i] && respects_n_format(args[i]))
// 		i++;
// 	return (i);
// 	//if y a pas de -n : return (0)
// 	// if y a un -n : return position du premier arg qui n'est pas -n
// }

int	check_n(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (!respects_n_format(args[i]))
			return (i);
		i++;
	}
	return (0);
	//if y a pas de -n : return (0)
	// if y a un -n : return position du premier arg qui n'est pas -n
}

// int	run_echo(char **args)
// {
// 	int	i;
// 	int	n_option;

// 	if (!args[1])
// 	{
// 		ft_putchar_fd('\n', 1);
// 		return (1);
// 	}
// 	i = check_n(args);
// }

int main(int argc, char **argv)
{
	// char test[] = "-nnnnn";
	// char test[3][10] = {"echo", "-n", "bonjour"};
	// char test1[] = "echo -nnnnn bonjour";
	// char test2[] = "echo -n -n -n -n bonjour";

	// char test3[] = "echo -n n n n bonjour";
	// char test4[] = "echo -n-n-n bonjour";
	// char test5[] = "echo -nno bonjour";
	// char test6[] = "echo --nn bonjour";
	// printf("1 ?\n");
	printf("%d\n", check_n(argv));
	// printf("%d\n", respects_n_format(argv));
	// printf("%d\n", check_n(test1));
	// printf("%d\n", check_n(test2));
	// printf("0 ?\n");
	// printf("%d\n", check_n(test3));
	// printf("%d\n", check_n(test4));
	// printf("%d\n", check_n(test5));
	// printf("%d\n", check_n(test6));
}