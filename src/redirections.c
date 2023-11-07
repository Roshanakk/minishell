/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:09:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/07 11:13:37 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	open_all_files(t_general *general, char **redir, e_token_types *redir_type)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (redir_type[i] == REDIR_IN)
		{
			if (open(redir[i], O_RDONLY, 000644) == -1)
			{
				ft_printf("minishell: %s: No such file or directory", redir[i]);
				//exit
			}
		}
		else if (redir_type[i] == REDIR_OUT)
			open(redir[i], O_CREAT | O_WRONLY | O_TRUNC, 000644);
		i++;
	}
}

int	redirect_io_files(t_general *general, t_cmd *cmd)
{
	//ouvrir les fichiers
	//s'il y a un infile qui n'existe pas : exit
	//s'il y a un outfile qui n'existe pas : le creer
	open_all_files(general, cmd->redir, cmd->redir_type);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_general general;

// 	general = (t_general){0};
//  	general.cmdline = create_token_list("UUUSER", VAR);
// 	// insert_at_end(&general.cmdline, "OKKK", VAR);
// 	insert_at_end(&general.cmdline, "echo", WORD);
// 	insert_at_end(&general.cmdline, "-n", WORD);
// 	insert_at_end(&general.cmdline, "bonjour", WORD);
// 	// insert_at_end(&general.cmdline, "USER", VAR);
// 	// insert_at_end(&general.cmdline, "|", PIPE);
// 	insert_at_end(&general.cmdline, "outfile", REDIR_OUT);
// 	// insert_at_end(&general.cmdline, "echo", WORD);

	
// 	convert_token_lst_to_tab(&general, general.cmdline);
// 	open_all_files(&general, general.all_cmds->redir, general.all_cmds->redir_type);
// 	ft_free_general(&general);

// }