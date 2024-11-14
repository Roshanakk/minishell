/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:11:52 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/06 12:33:24 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **dup_env)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (dup_env[i])
	{
		ft_putstr_fd("declare -x ", 1);
		flag = 1;
		j = 0;
		while (dup_env[i][j])
		{
			ft_putchar_fd(dup_env[i][j], 1);
			if (dup_env[i][j] == '=' && flag)
			{
				ft_putchar_fd('"', 1);
				flag--;
			}
			j++;
		}
		if (!flag)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

size_t	len_until_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		return (i);
	return (0);
}

int	check_for_plus_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i - 1] && str[i - 1] == '+')
		return (1);
	return (0);
}

int	is_not_underscore(char *str)
{
	if (ft_strcmp(str, "_"))
		return (1);
	else
		return (0);
}

int	update_env(t_general *general)
{
	ft_free_array(general->env_tab, ft_array_size(general->env_tab));
	convert_env_to_tab(general);
	return (EXIT_SUCCESS);
}
