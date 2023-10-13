/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:55:03 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/13 11:47:29 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int respects_n_format(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-' || !str[1])
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

/*   return la position du premier arg apres l'option -n (ou -nnnn, etc)    */
int	check_n(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!respects_n_format(args[i]))
			return (i);
		i++;
	}
	return (0);
}

/* 
	ATTENTION
   args = { "echo", "-n", "bonjour"}
	donc args[0] = "echo" 
*/

int	run_echo(char **args)
{
	int	i;
	int	n_option;
	char c;

	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	i = check_n(args);
	n_option = i > 1 ? 1 : 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (n_option);
}

// int main(int argc, char **argv)
// {
// 	run_echo(argv);
// 	// printf("%d\n", respects_n_format("-"));
// }