/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:10:38 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/16 11:37:46 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	close_and_free(t_fds_struct *fds, int flag)
{
	safe_close(fds->infile, &fds, NULL, 0);
	safe_close(fds->outfile, &fds, NULL, 0);
	safe_close(fds->tmp_fd, &fds, NULL, 0);
	ft_free_fds_struct(&fds); 
	if (flag == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);	
}

int	ft_free_cmd_items(t_cmd_items **cmd_items)
{
	ft_free_array((*cmd_items)->cmd, ft_cmpt((*cmd_items)->arg, ' '));
	free((*cmd_items)->arg);
	free((*cmd_items)->path);
	free(*cmd_items);
	return (1);
}

int	ft_free_fds_struct(t_fds_struct **fds)
{
	free((*fds)->pid);
	free(*fds);
	return (1);
}