/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:09:58 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/07 15:43:17 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	safe_close(int fd, t_general *general)
{
	if (close(fd) == -1)
	{
		ft_free_general(general);
		exit(EXIT_FAILURE);
	}
	return ;
}

//1 : infile : O_RDONLY
//2 : outfile : O_CREATE | O_WRONLY | O_TRUNC
int	safe_open(char *file, int flag, t_general *general)
{
	int	fd;

	fd = -1;
	if (flag == 1)
	{
		fd = open(file, O_RDONLY, 000777);
		if (fd == -1)
		{
			ft_printf("minishell : %s: No such file or directory\n", file);
			ft_free_general(general);
			exit(EXIT_FAILURE);
		}
	}
	else if (flag == 2)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 000777);
		if (fd == -1)
		{
			ft_free_general(general);
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

int	open_all_files(t_general *general, char **redir_in, char **redir_out)
{
	int	i;
	int	fd_in;
	int	fd_out;

	if (!general || !redir_in[0] || !redir_out[0])
		return (EXIT_FAILURE);
	//A METTRE AVANT, DANS FONCTION MINISHELL
	// general->pipeline = malloc(sizeof(t_pipe));
	// if (!general->pipeline)
	// 	return (EXIT_FAILURE);
	
	i = 0;
	while (redir_in[i])
	{
		fd_in = safe_open(redir_in[i], 1, general);
		if (redir_in[i + 1])
			safe_close(fd_in, general);
		else
			general->pipeline->infile = fd_in;
		i++;
	}
	i = 0;
	while (redir_out[i])
	{
		fd_out = safe_open(redir_out[i], 2, general);
		if (redir_out[i + 1])
			safe_close(fd_out, general);
		else
			general->pipeline->outfile = fd_out;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	redirect_io_files(t_general *general, t_pipe *pipeline, t_cmd *cmd)
{
	//ouvrir les fichiers
	open_all_files(general, cmd->redir_in, cmd->redir_out);
	// ft_printf("%d\n", pipeline->infile);
	//redirection infile s'il existe
	if (pipeline->infile != -1)
	{
		if (dup2(pipeline->infile, STDIN_FILENO) == -1)
		{
			ft_free_general(general);
			exit(EXIT_FAILURE);
		}
	}
	if (pipeline->outfile != -1)
	{
		if (dup2(pipeline->outfile, STDOUT_FILENO) == -1)
		{
			ft_free_general(general);
			exit(EXIT_FAILURE);
		}
	}
	//redirection outfile s'il existe

	
}


// int main(int argc, char **argv, char **envp)
// {
// 	t_general general;

// 	general = (t_general){0};
//  	general.cmdline = create_token_list("word", WORD);
// 	// insert_at_end(&general.cmdline, "infile2.txt", REDIR_IN);
// 	// insert_at_end(&general.cmdline, "infile3.txt", REDIR_IN);
// 	// insert_at_end(&general.cmdline, "outfile1", REDIR_OUT);
// 	// insert_at_end(&general.cmdline, "outfile2", REDIR_OUT);
// 	// insert_at_end(&general.cmdline, "outfile_wesh", REDIR_OUT);

// 	convert_token_lst_to_tab(&general, general.cmdline);
	
// 	open_all_files(&general, general.all_cmds->redir_in, general.all_cmds->redir_out);
// 	ft_free_general(&general);
// 	return (0);
// }
