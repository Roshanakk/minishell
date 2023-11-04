/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:41:40 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/04 19:13:00 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_exit(t_general *general)
{
	int	status;
	int	i;

	//remplacer par g_status
	status = 1;
	if (general->env_tab)
		ft_free_array(general->env_tab, ft_lstsize(general->env_lst) - 1);
	if (general->env_lst)
		ft_lstclear(&general->env_lst);
	i = 0;
	if (general->all_cmds)
	{
		while (i < ft_nb_of_pipes(general->cmdline) + 1)
		{
			free((general->all_cmds + i)->cmd);
			free((general->all_cmds + i)->redir);
			free((general->all_cmds + i)->redir_type);
			i++;
			printf("on a free les features de all_cmds\n");
		}
		free(general->all_cmds);
		printf("on a free all_cmds\n");
	}
	if (general->cmdline)
		ft_token_lst_clear(&general->cmdline);
	exit(status);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_general	general;
//     general = (t_general){0};
// 	if (create_env_lst(envp, &general))
// 		return (EXIT_FAILURE);
// 	if (convert_env_to_tab(&general))
// 		return (ft_lstclear(&(general.env_lst)), EXIT_FAILURE);
//     ft_exit(&general);
// 	return (0);
// }

int main(int argc, char**argv, char **envp)
{
	t_general general;

	general = (t_general){0};
	if (create_env_lst(envp, &general))
		return (EXIT_FAILURE);
 	general.cmdline = create_token_list("infile1", REDIR_IN);
	insert_at_end(&general.cmdline, "echo", WORD);
	insert_at_end(&general.cmdline, "-n", WORD);
	insert_at_end(&general.cmdline, "bonjour", WORD);
	insert_at_end(&general.cmdline, "helm.txt", REDIR_OUT);
	// insert_at_end(&general.cmdline, "bonjour", PIPE);
	// insert_at_end(&general.cmdline, "cat", WORD);
	// insert_at_end(&general.cmdline, "helm.txt", REDIR_OUT);
	
	read_token_lst(&general, general.cmdline);

	ft_exit(&general);

	return 0;
}