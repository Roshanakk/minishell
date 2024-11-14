/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:21:03 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/06 15:03:24 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	deal_with_hyphen_error(char *arg_i)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putchar_fd('-', 2);
	if (arg_i[1])
		ft_putchar_fd(arg_i[1], 2);
	ft_putendl_fd(": invalid option", 2);
	return (2);
}

int	deal_with_errors(char *arg_i, bool *error)
{
	if (ft_strlen(arg_i) > 1 && (!ft_strncmp(arg_i, "-", 1)
			|| !ft_strncmp(arg_i, "--", 2)))
		return (deal_with_hyphen_error(arg_i));
	if (!check_valid_identifier(arg_i))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg_i, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*error = true;
	}
	return (EXIT_SUCCESS);
}
