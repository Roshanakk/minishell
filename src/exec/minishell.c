/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balacam <balacam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:14:41 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/08 11:38:45 by balacam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nb_pipes(t_token *cmdline)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = cmdline;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

void	create_std_backups(t_pipe *pipeline, t_general *general)
{
	pipeline->stdin_backup = safe_dup(STDIN_FILENO, general);
	pipeline->stdout_backup = safe_dup(STDOUT_FILENO, general);
}

int	minishell(t_general *general)
{
	int	test_heredoc;

	general->pipeline = malloc(sizeof(t_pipe));
	if (!general->pipeline)
		return (EXIT_FAILURE);
	test_heredoc = convert_token_lst_to_tab(general->cmdline, general);
	if (test_heredoc && test_heredoc != 130)
	{
		ft_free_general(general);
		exit (2);
	}
	if (g_sigtype == SIGINT)
	{
		general->exit_code = 130;
		g_sigtype = SIGEMPTY;
		return (130);
	}
	set_signals_child();
	if (!ft_nb_of_pipes(general->cmdline))
		general->exit_code = execute_one_cmd(general->all_cmds,
				general->pipeline, general);
	else
		general->exit_code = execute_cmdline(general->all_cmds,
				general->pipeline, general);
	return (0);
}
