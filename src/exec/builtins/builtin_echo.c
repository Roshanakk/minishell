/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:55:03 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/06 15:16:41 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	respects_n_format(char *str)
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

int	check_n(char **cmd, int *n_option)
{
	int	i;

	*n_option = 0;
	i = 1;
	if (cmd[i] && respects_n_format(cmd[i]))
	{
		*n_option = 1;
		i++;
	}
	while (cmd[i] && respects_n_format(cmd[i]))
		i++;
	return (i);
}

/* 
	ATTENTION
   cmd = { "echo", "-n", "bonjour"}
	donc cmd[0] = "echo" 
*/

int	run_echo(char **cmd)
{
	int		i;
	int		n_option;

	if (!cmd[1])
	{
		ft_putchar_fd('\n', 1);
		return (EXIT_SUCCESS);
	}
	i = check_n(cmd, &n_option);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}

// int main(int argc, char **argv)
// {
// 	run_echo(argv + 1);
// 	// printf("ici : %s\n", (argv + 1)[1]);
// 	// printf("%d\n", respects_n_format("-"));
// }