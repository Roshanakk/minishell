/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:46:24 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/07 16:46:09 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	ft_free_general(t_general *general)
{
	int	i;

	i = 0;
	if (general->cmdline)
	{
		while (i < ft_nb_of_pipes(general->cmdline) + 1)
		{
			free((general->all_cmds + i)->cmd);
			free((general->all_cmds + i)->redir_in);
			free((general->all_cmds + i)->redir_out);
			i++;
		}
		ft_token_lst_clear(&general->cmdline);
	}
	if (general->pipeline)
		free(general->pipeline);
	if (general->all_cmds)
		free(general->all_cmds);
}


int	ft_nb_pipes(t_token *cmdline)
{
	int	i;
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

int	execute_cmd(t_general *general, t_cmd *cmd_i)
{
	redirect_io_files(general, general->pipeline, cmd_i);
	//executer builtin si la cmd est un builtin
	//executer bin si la cmd est un bin
	// ft_printf("%s\n", cmd_i->cmd[0]);
	execve("/usr/bin/grep", cmd_i->cmd, NULL);
	// execve(cmd_i->cmd[0], cmd_i->cmd, NULL);
	return (EXIT_FAILURE);
}

// int execute_cmdline(t_general *general, t_cmd *all_cmds, t_pipe *pipeline)
// {
// 	t_token *tmp;
// 	int		i;
// 	int		nb_of_pipes;
// 	int		nb_of_children;
// 	nb_of_pipes = ft_nb_of_pipes(general->cmdline);
// 	nb_of_children = nb_of_pipes + 1;
// 	i = 0;
// 	// while (i < nb_of_children)
// 	// {
// 		pipeline->pid = fork();
// 		if (pipeline->pid < 0)
// 			return (EXIT_FAILURE);
// 		else if (pipeline->pid == 0)
// 			execute_cmd(general, all_cmds + i);
// 	// 	i++;
// 	// }
// }

int minishell(t_general *general)
{
	//PARSING : CREATION DE LA LISTE DE TOKENS
	general->cmdline = create_token_list("infile1.txt", REDIR_IN);
	insert_at_end(&general->cmdline, "grep", WORD);
	insert_at_end(&general->cmdline, "z", WORD);
	insert_at_end(&general->cmdline, "nouveau.txt", REDIR_OUT);
	// insert_at_end(&general->cmdline, "-la", WORD);

	//CONVERSION EN TABLEAU
	convert_token_lst_to_tab(general, general->cmdline);

	//PREP_EXECUTION
	general->pipeline = malloc(sizeof(t_pipe));
	if (!general->pipeline)
		return (EXIT_FAILURE);
	
	//EXECUTION
	// execute_cmdline(general, general->all_cmds, general->pipeline);
	execute_cmd(general, general->all_cmds);
	// ft_printf("on est la\n");

	//FREE
	ft_free_general(general);

}

int main(int argc, char **argv, char **envp)
{
	t_general general;

	general = (t_general){0};
	minishell(&general);
	return (0);
}