/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fd_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:46:21 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/09/22 15:08:32 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	safe_close(int fd, t_fds_struct **fds, t_cmd_items **cmd_items, int flag)
{
	if (close(fd) == -1)
	{
		if (flag == 1)
			ft_free_cmd_items(cmd_items);
		ft_free_fds_struct(fds);
		exit(EXIT_FAILURE);
	}
	return ;
}

void	dup_tmp_fd(int *previous_pipe, t_fds_struct *fds, t_cmd_items *cmd_items, int flag)
{
	fds->tmp_fd = dup(*previous_pipe);
	if (!fds->tmp_fd)
	{
		safe_close(fds->infile, &fds, &cmd_items, flag);
		safe_close(fds->outfile, &fds, &cmd_items, flag);
		safe_close(fds->pipefd[0], &fds, &cmd_items, flag);
		safe_close(fds->pipefd[1], &fds, &cmd_items, flag);
		ft_free_cmd_items(&cmd_items);
		ft_free_fds_struct(&fds);
		exit (EXIT_FAILURE);		
	}
}