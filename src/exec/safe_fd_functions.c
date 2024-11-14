/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fd_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:46:21 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/12/11 13:50:31 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_dup(int fd, t_general *general)
{
	int	dup_fd;

	dup_fd = dup(fd);
	if (dup_fd == -1)
	{
		ft_free_general(general);
		exit(EXIT_FAILURE);
	}
	return (dup_fd);
}

void	safe_close(int fd, t_general *general)
{
	if (close(fd) == -1)
	{
		ft_free_general(general);
		exit(EXIT_FAILURE);
	}
	return ;
}

int	safe_open_heredoc(char *delimiter, t_general *general)
{
	int	fd;

	fd = open(delimiter, O_CREAT | O_WRONLY | O_TRUNC, 000777);
	if (fd == -1)
	{
		ft_free_general(general);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	open_out_or_append(char *file, t_token_types flag)
{
	int	fd;

	fd = -1;
	if (flag == REDIR_OUT)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 000777);
		if (fd == -1)
		{
			perror(file);
			return (-1);
		}
	}
	else if (flag == APPEND)
	{
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 000777);
		if (fd == -1)
		{
			perror(file);
			return (-1);
		}
	}
	return (fd);
}

int	safe_open_io_files(char *file, t_token_types flag, t_general *general)
{
	int	fd;

	fd = -1;
	if (flag == REDIR_IN)
	{
		fd = open(file, O_RDONLY, 000777);
		if (fd == -1)
		{
			print_error("minishell", file, NULL, "No such file or directory");
			return (deal_with_infile_error(general));
		}
	}
	else if (flag == REDIR_OUT || flag == APPEND)
	{
		fd = open_out_or_append(file, flag);
		return (fd);
	}
	else if (flag == HEREDOC)
	{
		fd = open("heredoc.tmp", O_RDONLY, 000777);
		general->heredoc_fd = fd;
	}
	if (fd == -1 && ft_nb_of_pipes(general->cmdline))
		exit_failure_and_free(general);
	return (fd);
}
