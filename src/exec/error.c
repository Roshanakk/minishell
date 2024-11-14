/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:41:53 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/11 13:50:03 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (-1);
}

int	deal_with_infile_error(t_general *general)
{
	safe_close(general->pipeline->stdin_backup, general);
	safe_close(general->pipeline->stdout_backup, general);
	if (ft_nb_of_pipes(general->cmdline))
	{
		safe_close(general->pipeline->prev_pipe, general);
		safe_close(general->pipeline->pipefd[0], general);
		safe_close(general->pipeline->pipefd[1], general);
		exit_failure_and_free(general);
	}
	return (-1);
}
