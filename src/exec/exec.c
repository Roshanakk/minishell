/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:04:17 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/09 19:06:18 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_and_update_prevpipe(t_pipe *pipeline, int index,
	int nb_of_children, t_general *general)
{
	int	is_last_cmd;

	is_last_cmd = 0;
	if (nb_of_children - index - 1 == 0)
		is_last_cmd = 1;
	safe_close(pipeline->pipefd[1], general);
	if (!is_last_cmd)
	{
		safe_close(pipeline->prev_pipe, general);
		pipeline->prev_pipe = safe_dup(pipeline->pipefd[0], general);
	}
	safe_close(pipeline->pipefd[0], general);
}

int	there_is_a_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

//execute_cmd : fonction definie pour plusieurs pipes, pas s'il n'y a
//qu'une seule cmd
int	execute_cmd(t_cmd *cmd_i, t_pipe *pipeline, t_general *general)
{
	char	*cmd_path;

	if (there_is_a_slash(cmd_i->cmd[0]))
	{
		cmd_path = cmd_i->cmd[0];
		if (access(cmd_path, F_OK))
			return (deal_with_binary(cmd_path, general));
	}
	else
		cmd_path = get_path(general->env_tab, cmd_i->cmd[0]);
	safe_close(pipeline->stdin_backup, general);
	safe_close(pipeline->stdout_backup, general);
	if (contains_type_redir_in(cmd_i->redir, cmd_i->redir_type))
		safe_close(pipeline->infile, general);
	if (ft_nb_of_pipes(general->cmdline))
		safe_close_pipefd(pipeline, general);
	else if (contains_type_out_or_append(cmd_i->redir, cmd_i->redir_type))
		safe_close(pipeline->outfile, general);
	if (!cmd_path)
		return (error_cmd_not_found(cmd_i->cmd[0], general));
	execve(cmd_path, cmd_i->cmd, general->env_tab);
	return (error_cmd_not_found(cmd_i->cmd[0], general));
}

static void	exec_child(t_cmd *cmd_i, t_pipe *pipeline, t_general *general)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if ((cmd_i)->cmd[0] && is_builtin((cmd_i)->cmd[0]))
	{
		ret = run_builtin(cmd_i, general);
		if (ret != CMD_NOT_FOUND)
			exit_builtin_error(ret, general);
	}
	else if ((cmd_i)->cmd[0])
		ret = execute_cmd(cmd_i, pipeline, general);
	if (ret)
		exit (ret);
}

int	execute_cmdline(t_cmd *all_cmds, t_pipe *pipeline, t_general *general)
{
	int		i;
	int		nb_of_children;
	int		status;

	nb_of_children = ft_nb_of_pipes(general->cmdline) + 1;
	create_std_backups(pipeline, general);
	i = -1;
	pipeline->prev_pipe = safe_dup(STDIN_FILENO, general);
	while (++i < nb_of_children)
	{
		if (pipe(pipeline->pipefd) == -1)
			return (EXIT_FAILURE);
		pipeline->pid = safe_fork(general);
		if (pipeline->pid == 0)
		{
			redirect_io_files(all_cmds + i, i, nb_of_children, general);
			exec_child(all_cmds + i, pipeline, general);
		}
		close_pipe_and_update_prevpipe(pipeline, i, nb_of_children, general);
	}
	safe_close_remaining_files(pipeline, general);
	status = wait_children(pipeline->pid);
	return (status);
}
