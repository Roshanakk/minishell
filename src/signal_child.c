/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:39:49 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 15:41:49 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_child(int signal)
{
	(void) signal;
	write(1, "\n", 1);
}

void	set_signals_child(void)
{
	if (signal(SIGINT, &sig_child) == SIG_ERR
		|| signal(SIGQUIT, &sig_child) == SIG_ERR)
	{
		perror("signal.c");
		return ;
	}
}
