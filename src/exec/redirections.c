/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:09:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/11 11:52:35 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_all_files(t_general *general, t_cmd *cmd,
	char **redir, t_token_types *redir_type)
{
	int	i;
	int	fd;

	(void) cmd;
	if (!redir[0])
		return (EXIT_SUCCESS);
	if (!general)
		return (EXIT_FAILURE);
	i = 0;
	while (redir[i])
	{
		fd = safe_open_io_files(redir[i], redir_type[i], general);
		if (fd == -1)
			return (EXIT_FAILURE);
		if (must_close_previous_file(redir, redir_type, i))
			safe_close(fd, general);
		else if (redir_type[i] == REDIR_IN || redir_type[i] == HEREDOC)
			general->pipeline->infile = fd;
		else if (redir_type[i] == REDIR_OUT || redir_type[i] == APPEND)
			general->pipeline->outfile = fd;
		i++;
	}
	return (EXIT_SUCCESS);
}

void	update_prevpipe(t_general *general, t_pipe *pipeline,
	t_cmd *cmd_i, int is_first_cmd)
{
	(void)is_first_cmd;
	if (cmd_i->redir[0]
		&& (contains_type_redir_in(cmd_i->redir, cmd_i->redir_type))
		&& pipeline->infile)
	{
		safe_close(pipeline->prev_pipe, general);
		pipeline->prev_pipe = safe_dup(pipeline->infile, general);
	}
}

void	update_nextpipe(t_general *general, t_pipe *pipeline,
	t_cmd *cmd_i, int is_last_cmd)
{
	if (cmd_i->redir[0]
		&& contains_type_out_or_append(cmd_i->redir, cmd_i->redir_type)
		&& pipeline->outfile != -1)
	{
		pipeline->next_pipe = safe_dup(pipeline->outfile, general);
		safe_close(pipeline->outfile, general);
	}
	else if ((!cmd_i->redir[0]
			|| !contains_type_out_or_append(cmd_i->redir, cmd_i->redir_type))
		&& !is_last_cmd)
		pipeline->next_pipe = safe_dup(pipeline->pipefd[1], general);
	else if (is_last_cmd)
		pipeline->next_pipe = safe_dup(pipeline->stdout_backup, general);
}

void	redirect_io(t_general *general, t_pipe *pipeline, t_cmd *cmd_i)
{
	(void) cmd_i;
	if (dup2(pipeline->prev_pipe, STDIN_FILENO) == -1)
	{
		ft_free_general(general);
		exit(EXIT_FAILURE);
	}
	safe_close(pipeline->prev_pipe, general);
	if (dup2(pipeline->next_pipe, STDOUT_FILENO) == -1)
	{
		ft_free_general(general);
		exit(EXIT_FAILURE);
	}
	safe_close(pipeline->next_pipe, general);
}

void	redirect_io_files(t_cmd *cmd_i, int index,
	int nb_of_children, t_general *general)
{
	int	is_first_cmd;
	int	is_last_cmd;

	is_first_cmd = 0;
	if (index == 0)
		is_first_cmd = 1;
	is_last_cmd = 0;
	if (nb_of_children - index - 1 == 0)
		is_last_cmd = 1;
	open_all_files(general, cmd_i, cmd_i->redir, cmd_i->redir_type);
	update_prevpipe(general, general->pipeline, cmd_i, is_first_cmd);
	update_nextpipe(general, general->pipeline, cmd_i, is_last_cmd);
	redirect_io(general, general->pipeline, cmd_i);
}
