/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:04:52 by azarraffi         #+#    #+#             */
/*   Updated: 2023/10/19 15:10:35 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// void	remove(char *arg, t_list *env_lst)
// {
// 	int	i;
// 	t_list	*var_exists;

// 	var_exists = node_in_env(env_lst, )
// 	i = 0;
// 	while 
// }

// int	run_unset(char **args, t_envp *env)
// {
// 	int	i;

// 	if (!args[1])
// 		return (EXIT_SUCCESS);
// 	i = ft_array_size(args) - 1;
// 	while (i)
// 	{
// 		if (!check_valid_identifier(args[i]))
// 		{
// 			ft_putstr_fd("minishell: unset: `", 1);
// 			ft_putstr_fd(args[i], 1);
// 			ft_putstr_fd("`: not a valid identifier\n", 1);
// 			// printf("not valid\n");
// 		}
// 		else
// 			remove(args[i], env->lst);
// 		i--;
// 	}
	
// 	return (EXIT_SUCCESS);
// }

// int main(int argc, char **argv)
// {
// 	run_unset(argv);
// }