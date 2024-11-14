/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:38:33 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 15:48:33 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	deal_with_binary(char *cmd_path, t_general *general)
{
	print_error("minishell",
		cmd_path, NULL, "No such file or directory");
	ft_free_general(general);
	return (CMD_NOT_FOUND);
}

void	safe_close_pipefd(t_pipe *pipeline, t_general *general)
{
	safe_close(pipeline->pipefd[0], general);
	safe_close(pipeline->pipefd[1], general);
}

int	error_cmd_not_found(char *bad_cmd, t_general *general)
{
	print_error("minishell", bad_cmd, NULL, "command not found");
	ft_free_general(general);
	return (CMD_NOT_FOUND);
}

void	exit_builtin_error(int ret, t_general *general)
{
	safe_close(general->pipeline->stdin_backup, general);
	safe_close(general->pipeline->stdout_backup, general);
	safe_close(general->pipeline->pipefd[0], general);
	safe_close(general->pipeline->pipefd[1], general);
	ft_free_general(general);
	exit(ret);
}

void	safe_close_remaining_files(t_pipe *pipeline, t_general *general)
{
	safe_close(pipeline->prev_pipe, general);
	safe_close(pipeline->stdin_backup, general);
	safe_close(pipeline->stdout_backup, general);
}
