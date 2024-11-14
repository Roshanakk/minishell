/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:38:11 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/06 15:49:43 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	if (ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}

int	run_builtin(t_cmd *cmd_i, t_general *general)
{
	char	*pwd;
	int		ret;

	ret = CMD_NOT_FOUND;
	if (!ft_strcmp(cmd_i->cmd[0], "echo"))
		ret = run_echo(cmd_i->cmd);
	else if (!ft_strcmp(cmd_i->cmd[0], "env"))
		ret = run_env(general);
	else if (!ft_strcmp(cmd_i->cmd[0], "export"))
		ret = run_export(cmd_i->cmd, general);
	else if (!ft_strcmp(cmd_i->cmd[0], "unset"))
		ret = run_unset(cmd_i->cmd, general);
	else if (!ft_strcmp(cmd_i->cmd[0], "exit"))
		ret = run_exit(cmd_i->cmd, general);
	else if (!ft_strcmp(cmd_i->cmd[0], "cd"))
		ret = run_cd(cmd_i->cmd, general);
	else if (!ft_strcmp(cmd_i->cmd[0], "pwd"))
	{
		pwd = getcwd(NULL, 0);
		ft_putendl_fd(pwd, STDOUT_FILENO);
		free(pwd);
		ret = EXIT_SUCCESS;
	}
	return (ret);
}
