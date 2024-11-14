/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:59:31 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/09 19:33:05 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_cmd *cmd, t_pipe *pipeline, t_general *general)
{
	int	ret;

	ret = execute_cmd(cmd, pipeline, general);
	if (ret)
		exit (ret);
}

int	execute_one_cmd(t_cmd *all_cmds, t_pipe *pipeline, t_general *general)
{
	int	ret;
	int	status;

	status = EXIT_SUCCESS;
	create_std_backups(pipeline, general);
	if (open_all_files(general, all_cmds,
			all_cmds->redir, all_cmds->redir_type))
		return (EXIT_FAILURE);
	redirect_single_cmd_io(all_cmds, pipeline, general);
	if (all_cmds->cmd[0] && is_builtin(all_cmds->cmd[0]))
	{
		ret = run_builtin(all_cmds, general);
		if (ret)
			return (ret);
	}
	else if (all_cmds->cmd[0])
	{
		pipeline->pid = safe_fork(general);
		if (pipeline->pid == 0)
			exec_child(all_cmds, pipeline, general);
		status = wait_children(pipeline->pid);
	}
	restore_single_cmd_io(all_cmds, pipeline, general);
	return (status);
}
