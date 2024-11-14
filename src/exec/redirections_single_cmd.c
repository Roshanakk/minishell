/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_single_cmd.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:51:47 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/09 13:01:48 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_single_cmd_io(t_cmd *cmd, t_pipe *pipeline, t_general *general)
{
	if (cmd->redir[0] && (contains_type_redir_in(cmd->redir, cmd->redir_type))
		&& pipeline->infile && pipeline->infile != -1)
	{
		if (dup2(pipeline->infile, STDIN_FILENO) == -1)
		{
			ft_free_general(general);
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->redir[0]
		&& contains_type_out_or_append(cmd->redir, cmd->redir_type)
		&& pipeline->outfile && pipeline->outfile != -1)
	{
		if (dup2(pipeline->outfile, STDOUT_FILENO) == -1)
		{
			ft_free_general(general);
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

// on verifie qu'il y a des types REDIR_IN 
//et pas seulement des types HEREDOC dans le
// tableau redir_in, sinon on ne "retablit" pas STDIN
int	restore_single_cmd_io(t_cmd *cmd, t_pipe *pipeline, t_general *general)
{
	if (contains_type_redir_in(cmd->redir, cmd->redir_type))
	{
		if (dup2(pipeline->stdin_backup, STDIN_FILENO) == -1)
		{
			ft_free_general(general);
			exit(EXIT_FAILURE);
		}
		safe_close(pipeline->infile, general);
	}
	if (contains_type_out_or_append(cmd->redir, cmd->redir_type))
	{
		if (dup2(pipeline->stdout_backup, STDOUT_FILENO) == -1)
		{
			ft_free_general(general);
			exit(EXIT_FAILURE);
		}
		safe_close(pipeline->outfile, general);
	}
	safe_close(pipeline->stdin_backup, general);
	safe_close(pipeline->stdout_backup, general);
	return (EXIT_SUCCESS);
}
