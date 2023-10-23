/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:20:34 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/10/23 11:05:02 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include <sys/types.h>
#include <sys/wait.h>

// NOTES //
// Pour le moment, 2 choses a free : lst et tab de ma structure envp ci-dessous //

typedef struct s_envp {
	t_list	*lst;			// on copie envp dans une liste chainee
	char	**tab;			// on convertit en tab pour envoyer a execve
} t_envp;

typedef struct s_cmd_items {
	char *arg;
	char **cmd;
	char *path;
	char *args_cmd[4];

} t_cmd_items;

typedef struct s_fds {
	int *pid;
	int	infile;
	int	outfile;
	int pipefd[2];
	int	tmp_fd;
} t_fds_struct;

//PIPEX.C
// void exec_cmd(char **argv, t_cmd_items *cmd_items, int *input_file, int *next_pipe[2]);
// int 	parsing(int argc, char **argv);
// int	do_pipe(char **argv, char **envp, int index_cmd, int pid);
// void exec_cmd(t_fds_struct *fds, t_cmd_items *cmd_items, int index_cmd);



//CREATE_STRUCTS.C
int	create_fds_struct(t_fds_struct **fds, char **argv, int argc);
int		create_pid_table(int **pid, int argc);
int	open_files(int *infile, int *outfile, char **argv, int argc);
int	create_cmd_items(t_cmd_items **cmd_items, char *argv_cmd, char **argv);


//FREE.C
int	ft_free_cmd_items(t_cmd_items **cmd_items);
int	ft_free_fds_struct(t_fds_struct **fds);
int	close_and_free(t_fds_struct *fds, int flag);


//SAFE_FD_FUNCTIONS.C
void	safe_close(int fd, t_fds_struct **fds, t_cmd_items **cmd_items, int flag);
void	dup_tmp_fd(int *previous_pipe, t_fds_struct *fds, t_cmd_items *cmd_items, int flag);

//ENV
int	create_env_lst(char **envp, t_envp *env);
int	convert_env_to_tab(t_envp *env);
char *get_path(char **envp, char *cmd);

//
t_list	*node_in_env(t_list *lst, char *var_and_value);
size_t	len_until_equal_sign(char *str);
int	check_valid_identifier(char *str);

#endif