/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:04:10 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/10 15:20:01 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int exec_cmd(t_fds_struct *fds, t_cmd_items *cmd_items, int *input_pipe, int *next_pipe)
{
	if (dup2(*input_pipe, STDIN_FILENO) == -1 
		|| dup2(*next_pipe, STDOUT_FILENO) == -1)
	{
		safe_close(fds->infile, &fds, &cmd_items, 1);
		if (fds->infile != fds->tmp_fd)
			safe_close(fds->tmp_fd, &fds, &cmd_items, 1);
		safe_close(fds->outfile, &fds, &cmd_items, 1);
		safe_close(fds->pipefd[0], &fds, &cmd_items, 1);
		safe_close(fds->pipefd[1], &fds, &cmd_items, 1);
		ft_free_cmd_items(&cmd_items);
		ft_free_fds_struct(&fds);
		exit (EXIT_FAILURE);
	}
	return(execve(cmd_items->path, cmd_items->cmd, NULL));		
}

// int parsing(int argc, char **argv)
// {
// 	if (argc < 5)
// 		return (1);
// 	else
// 		return (0);
// }

void	close_pipe_and_new_tmp(int argc, t_fds_struct *fds, t_cmd_items *cmd_items, int index_cmd)
{
	safe_close(fds->pipefd[1], &fds, &cmd_items, 1);
	safe_close(fds->tmp_fd, &fds, &cmd_items, 1);
	if (index_cmd < argc - 2)
		dup_tmp_fd(&(fds->pipefd[0]), fds, cmd_items, 1);
	safe_close(fds->pipefd[0], &fds, &cmd_items, 1);
	ft_free_cmd_items(&cmd_items);	
}

int	do_pipe(int argc, char **argv, char **envp, t_fds_struct *fds, int index_cmd)
{
	t_cmd_items *cmd_items;
	int i;

	i = index_cmd - 2;
	if (pipe(fds->pipefd) == -1)
		return (EXIT_FAILURE);
	if (create_cmd_items(&cmd_items, argv[index_cmd], argv))
		return (EXIT_FAILURE);
	fds->pid[i] = fork();
	if (fds->pid[i] < 0)
		return (ft_free_cmd_items(&cmd_items));
	if (fds->pid[i] == 0)
	{
		if (index_cmd < argc - 2)
			exec_cmd(fds, cmd_items, &(fds->tmp_fd), &(fds->pipefd[1]));
		else if (index_cmd == argc - 2)
			exec_cmd(fds, cmd_items, &(fds->tmp_fd), &(fds->outfile));
	}
	close_pipe_and_new_tmp(argc, fds, cmd_items, index_cmd);
	return (EXIT_SUCCESS);
}

// int main (int argc, char **argv, char **envp) 
// {	
// 	int			i;
// 	t_fds_struct *fds;
	
// // 	if (!parsing(argc, argv))
// // 		return (EXIT_FAILURE);
// 	if (create_fds_struct(&fds, argv, argc))
// 		return (EXIT_FAILURE);
// 	dup_tmp_fd(&(fds->infile), fds, NULL, 0);
// 	i = 1;
// 	while (i++ < argc - 2)
// 	{
// 		if (do_pipe(argc, argv, envp, fds, i) == EXIT_FAILURE)
// 			close_and_free(fds, 1);
// 	}
// 	i = -1;
// 	while (i++ < argc - 4)
// 		waitpid(fds->pid[i], NULL, 0);
// 	close_and_free(fds, 0);
// 	return (EXIT_SUCCESS);
// }
