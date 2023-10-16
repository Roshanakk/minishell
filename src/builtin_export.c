/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:04:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/16 13:08:41 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char **dup_array(char **array)
{
	char	**dup;
	int		i;

	dup = malloc(sizeof(char *) * ft_array_size(array));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < ft_array_size(array))
	{
		dup[i] = ft_strdup(array[i]);
		if (!dup[i])
			return (ft_free_array(dup, i));
		i++;
	}
	return (dup);
}

void	ft_swap(char **a, char **b)
{
	char	*a1;

	a1 = *a;
	*a = *b;
	*b = a1;
}

void	sort(char **array)
{
	char	*tmp;
	int	i;
	int	j;

	j = 0;
	while (j < ft_array_size(array))
	{
		i = 0;
		while (i < ft_array_size(array))
		{
			if (array[i + 1] && ft_strcmp(array[i], array[i + 1]) > 0)
				ft_swap(&array[i], &array[i + 1]);
			i++;
		}
		j++;
	}
}

int run_export(char **args, t_envp *env)
{
	int	i;
	char **dup_env;

	dup_env = env->tab;
	if (!args[1])
	{
		sort(dup_env);
		return (1);
	}
	i = 0;
	while (dup_env[i])
	{
		printf("%s\n", dup_env[i]);
		i++;
	}
	/////////////////////////
	/////////////////////////
	/////////////////////////
	return (1);
}

int main(int argc, char **argv)
{
	run_export(argv);
	// sort(new_argv);
	// int i = 0;
	// while (new_argv[i])
	// {
	// 	printf("%s\n", new_argv[i]);
	// 	i++;
	// }
	// ft_free_array(new_argv, ft_array_size(new_argv));
}