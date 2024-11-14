/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:38:36 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 15:41:28 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_heredoc(int signal)
{
	(void) signal;
	g_sigtype = SIGINT;
	if (close(STDIN_FILENO) == -1)
		exit (EXIT_FAILURE);
}

void	set_signals_heredoc(void)
{
	if (signal(SIGINT, &sig_heredoc) == SIG_ERR)
		perror("signal.c");
}
