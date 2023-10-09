/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:08:15 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/09/21 17:40:15 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	create_fds_struct(t_fds_struct **fds, char **argv, int argc)
{
	*fds = malloc(sizeof(t_fds_struct));
	if (!(*fds))
		return (EXIT_FAILURE);
	if (create_pid_table(&((*fds)->pid), argc))
		return (EXIT_FAILURE);
	if (open_files(&((*fds)->infile), &((*fds)->outfile), argv, argc))
		return (ft_free_fds_struct(fds), EXIT_FAILURE); 
	return (EXIT_SUCCESS);
}

int	create_pid_table(int **pid, int argc)
{
	*pid = malloc(sizeof(int) * (argc - 3));
	if (!pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	open_files(int *infile, int *outfile, char **argv, int argc)
{
	*infile = open(argv[1], O_RDONLY, 000644);
	if (*infile < 0)
	{
		ft_printf("%s: No such file or directory\n", argv[1]);
		return (EXIT_FAILURE);
	}
	*outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 000644);
	if (*outfile < 0)
	{
		perror("outfile");
		return (EXIT_FAILURE);
	}	
	return (EXIT_SUCCESS);
}

int	create_cmd_items(t_cmd_items **cmd_items, char *argv_cmd, char **argv)
{
	*cmd_items = malloc(sizeof(t_cmd_items));
	if (!(*cmd_items))
		return (EXIT_FAILURE);
	(*cmd_items)->arg = ft_strdup(argv_cmd);
	if (!((*cmd_items)->arg))
	{
		free(*cmd_items);
		return (EXIT_FAILURE);
	}
	(*cmd_items)->cmd = ft_split((*cmd_items)->arg, ' ');
	if (!((*cmd_items)->cmd))
	{
		free((*cmd_items)->arg);
		free(*cmd_items);
		return (EXIT_FAILURE);
	}
	(*cmd_items)->path = ft_strjoin("/usr/bin/", (*cmd_items)->cmd[0]);
	if (!((*cmd_items)->path))
	{
		ft_free_double_char((*cmd_items)->cmd, ft_cmpt(argv[2], ' '));	
		free((*cmd_items)->arg);
		free(*cmd_items);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
