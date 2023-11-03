/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:20:34 by rraffi-k          #+#    #+#             */
/*   Updated: 2023/11/03 11:09:35 by rraffi-k         ###   ########.fr       */
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


//PARSING
typedef enum e_token_types
{
	WORD,
	VAR,
	PIPE,
	HEREDOC,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	END
}    e_token_types;

typedef struct s_token
{
	char			*value;
	e_token_types	type;
	struct s_token	*next;
} t_token;

// NOTES //
// Pour le moment, 2 choses a free : lst et tab de ma structure envp ci-dessous //

typedef struct s_envp {
	t_list	*lst;			// on copie envp dans une liste chainee
	char	**tab;			// on convertit en tab pour envoyer a execve
} t_envp;

typedef struct s_cmd {
	char **cmd;				//																FREE
	char **redir;			//contient "value" (t_token) de la redirection					FREE
	e_token_types *redir_type;		//contient "type" (t_token) de la redirection					FREE
	
} t_cmd;

typedef struct s_pipe {
	int		nb_pipes;
	
} t_pipe;

typedef struct s_general {
	t_list	*env_lst;			// on copie envp dans une liste chainee						FREE
	char	**env_tab;	        // on convertit en tab pour envoyer a execve				FREE
	t_token *cmdline;			//															FREE (BUSE ?)
	t_cmd   *all_cmds;			//															FREE
	t_pipe	*pipeline;			
} t_general;

//PIPEX
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

//pipex.c
// void exec_cmd(char **argv, t_cmd_items *cmd_items, int *input_file, int *next_pipe[2]);
// int 	parsing(int argc, char **argv);
// int	do_pipe(char **argv, char **envp, int index_cmd, int pid);
// void exec_cmd(t_fds_struct *fds, t_cmd_items *cmd_items, int index_cmd);


//create_structs.c
int	create_fds_struct(t_fds_struct **fds, char **argv, int argc);
int		create_pid_table(int **pid, int argc);
int	open_files(int *infile, int *outfile, char **argv, int argc);
int	create_cmd_items(t_cmd_items **cmd_items, char *argv_cmd, char **argv);


//free.c
int	ft_free_cmd_items(t_cmd_items **cmd_items);
int	ft_free_fds_struct(t_fds_struct **fds);
int	close_and_free(t_fds_struct *fds, int flag);


//safe_fd_functions.c
void	safe_close(int fd, t_fds_struct **fds, t_cmd_items **cmd_items, int flag);
void	dup_tmp_fd(int *previous_pipe, t_fds_struct *fds, t_cmd_items *cmd_items, int flag);

//builtin_env
int	create_env_lst(char **envp, t_general *general);
int	convert_env_to_tab(t_general *general);
char *get_path(char **envp, char *cmd);

//builtin_export
t_list	*node_in_env(t_list *lst, char *var_and_value);
size_t	len_until_equal_sign(char *str);
int	check_valid_identifier(char *str);


//lst_token.c
t_token	*create_token_list(char *token, e_token_types type);
void	insert_at_end(t_token **head, char *str, e_token_types type);
void	ft_token_lst_clear(t_token **lst);


#endif