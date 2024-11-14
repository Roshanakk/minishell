/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:47:02 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 15:48:47 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_main(int signal)
{
	if (signal == SIGINT)
	{
		g_sigtype = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		return ;
}

void	set_signals_main(void)
{
	if (signal(SIGINT, &sig_main) == SIG_ERR)
	{
		perror("signal.c");
		return ;
	}
	signal(SIGQUIT, SIG_IGN);
}
