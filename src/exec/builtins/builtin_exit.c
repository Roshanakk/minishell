/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:41:40 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/06 15:18:00 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atoi(char *str, bool *error)
{
	unsigned long long	res;
	int					i;
	int					n;

	if (!is_numeric(str) || ft_strlen(str) > 20)
		return (set_error_true(error));
	i = 0;
	n = 1;
	res = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		deal_with_minus_sign(&n, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res = res + (str[i] - '0');
		if (res > 9223372036854775807)
			return (set_error_true(error));
		i++;
	}
	return (n * res);
}

void	close_files_run_exit(t_general *general)
{
	safe_close(general->pipeline->stdin_backup, general);
	safe_close(general->pipeline->stdout_backup, general);
	if (ft_nb_of_pipes(general->cmdline))
	{
		safe_close(general->pipeline->pipefd[0], general);
		safe_close(general->pipeline->pipefd[1], general);
	}	
}

int	deal_with_error(bool error, char **cmd, t_general *general)
{
	if (error)
	{
		print_error("minishell", "exit",
			cmd[1], "numeric argument required");
		general->exit_code = 2;
	}
	else if (ft_array_size(cmd) > 2)
	{
		print_error("minishell", "exit",
			NULL, "too many arguments");
		general->exit_code = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	run_exit(char **cmd, t_general *general)
{
	bool	error;

	error = false;
	if (cmd[1] && !ft_strcmp(cmd[1], "-9223372036854775808")
		&& ft_array_size(cmd) < 3)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		general->exit_code = EXIT_SUCCESS;
	}
	else if (cmd[1])
	{
		if (!ft_nb_of_pipes(general->cmdline))
			ft_putendl_fd("exit", STDOUT_FILENO);
		general->exit_code = (unsigned char)ft_atoi(cmd[1], &error);
		if (deal_with_error(error, cmd, general))
			return (EXIT_FAILURE);
	}
	close_files_run_exit(general);
	ft_free_general(general);
	exit(general->exit_code);
	return (2);
}
