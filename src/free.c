/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:07:18 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/09 16:27:51 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_general *general)
{
	if (general->env_tab)
		ft_free_array(general->env_tab, ft_lstsize(general->env_lst) - 1);
	if (general->env_lst)
		ft_lstclear(&(general->env_lst));
}

void	ft_free_all_but_env(t_general *general)
{
	if (general->cmdline)
	{
		if (general->all_cmds)
			ft_free_inside_all_cmds(general);
		ft_token_lst_clear(&general->cmdline);
	}
	if (!access("heredoc.tmp", F_OK))
		unlink("heredoc.tmp");
	if (general->pipeline)
		free(general->pipeline);
	if (general->all_cmds)
		free(general->all_cmds);
}

void	ft_free_inside_all_cmds(t_general *general)
{
	int	i;
	int	j;

	i = 0;
	while (i < ft_nb_of_pipes(general->cmdline) + 1)
	{
		j = 0;
		while ((general->all_cmds + i)->cmd[j])
		{
			free((general->all_cmds + i)->cmd[j]);
			j++;
		}
		free((general->all_cmds + i)->cmd);
		free((general->all_cmds + i)->redir);
		free((general->all_cmds + i)->redir_type);
		i++;
	}	
}

void	ft_free_general(t_general *general)
{
	if (general->cmdline)
	{
		ft_free_inside_all_cmds(general);
		ft_token_lst_clear(&general->cmdline);
	}
	if (general->pipeline)
		free(general->pipeline);
	if (general->all_cmds)
		free(general->all_cmds);
	if (general->env_tab)
		ft_free_array(general->env_tab, ft_lstsize(general->env_lst) - 1);
	if (general->env_lst)
		ft_lstclear(&(general->env_lst));
	rl_clear_history();
}
