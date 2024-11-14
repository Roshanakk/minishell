/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:26:22 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/01 18:16:42 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	decode(int child_status)
{
	if (WIFEXITED(child_status))
		child_status = WEXITSTATUS(child_status);
	else if (WIFSIGNALED(child_status))
	{
		if (WCOREDUMP(child_status))
			print_error("minishell", NULL, NULL, "child: core dump");
		child_status = WTERMSIG(child_status) + 128;
	}
	return (child_status);
}

int	wait_children(int last_pid)
{
	int	pid;
	int	child_status;
	int	final_status;

	final_status = EXIT_SUCCESS;
	while (true)
	{
		pid = waitpid(-1, &child_status, 0);
		if (pid < 0)
			break ;
		else if (pid == last_pid)
			final_status = decode(child_status);
	}
	return (final_status);
}

pid_t	safe_fork(t_general *general)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_free_general(general);
		exit(EXIT_FAILURE);
	}
	return (pid);
}
