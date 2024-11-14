/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraffi-k <rraffi-k@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:52:59 by balacam           #+#    #+#             */
/*   Updated: 2023/12/11 13:52:28 by rraffi-k         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <strings.h>
# include "libft.h"
# include "ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_PATH_LEN 4096
# define SIGEMPTY 0

# define CMD_NOT_FOUND 127

# define SUCCESS 0
# define FAILURE 1

/******************************************************************************
*								STRUCTURES									  *
******************************************************************************/

typedef enum token_types
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	END,
}	t_token_types;

enum e_quoting_status {
	DEFAULT,
	SQUOTE,
	DQUOTE
};

typedef struct s_token
{	
	char			*value;
	char			*value_backup;
	t_token_types	type;
	struct s_token	*next;
	int				status;
	int				squote_flag;
}	t_token;

typedef struct s_envp {
	t_list	*lst;
	char	**tab;
}	t_envp;

typedef struct s_cmd {
	char			**cmd;
	char			**redir;
	t_token_types	*redir_type;
}	t_cmd;

typedef struct s_pipe {
	__pid_t	pid;	
	int		infile;
	int		outfile;
	int		pipefd[2];
	int		prev_pipe;
	int		next_pipe;
	int		stdin_backup;
	int		stdout_backup;
}	t_pipe;

typedef struct s_general {
	t_list	*env_lst;
	char	**env_tab;
	t_token	*cmdline;
	t_cmd	*all_cmds;
	t_pipe	*pipeline;
	char	*heredoc_eof;
	char	*read_input;
	int		exit_code;
	int		heredoc_fd;
}	t_general;

//******** GLOBAL VARIABLE ********//

// extern int	g_status;
extern uint8_t	g_sigtype;

/******************************************************************************
*								LEXING										  *
******************************************************************************/

//******** TOKEN_LST_UTILS ********//
t_token			*create_token_list(char *value,
					char *backup, int type, int status);
void			insert_at_end(t_token **head, t_token *new_token);
void			ft_token_lst_clear(t_token **lst);
void			free_ptr(void *ptr);

//******** TOKEN_UTILS ********//
t_token_types	is_separator(char *str, int i);
int				set_status(int status,
					char *str, int i);
int				save_separator(t_token **token_lst,
					char *str, int index, int type);
int				save_word(t_token **token_lst,
					char *str, int index, int start);
int				save_word_or_sep(int *i, char *str,
					int start, t_general *general);

//******** TOKENS ********//
int				tokenization(t_general *general, char *str);

//******** TOOLS ********//
void			print_type(t_token *token);
void			print_value(t_token *current);
void			print_list(t_token **head);

//******** QUOTES ********//
bool			contains_quotes(const char *input_string);
int				remove_quotes(t_token **token_node);
int				handle_quotes(t_general *general);
bool			if_quotes_and_default(t_token **token_node, int i);
void			change_status_to_quote(t_token **token_node, int *i);
bool			change_back_to_default(t_token **token_node, int *i);
int				count_len(char *str, int count, int i);

/******************************************************************************
*								PARSING										  *
******************************************************************************/

//******** CHECK ********//
int				merge_value_heredoc(t_token **head, t_general *general);
int				merge_value_append(t_token **head, t_general *general);
int				sanitize_lst_tokens(t_token *head,
					t_general *general);
char			*expand_var(char *subword, t_general *general);
int				expand_if_needed(char *word, char **join,
					int *i, t_general *general);
int				replace_word_value(t_token **head,
					t_general *general);

int				check_for_dollar(const char *input_string);
int				deal_with_simple_quotes(char *word, char **join, int *i);
int				deal_with_double_quotes(char *word, char **join,
					int *i, t_general *general);
int				deal_with_characters(char *word, char **join,
					int *i, t_general *general);
void			init_values(char **join, int *i, int *start);
void			pass_extra_quotes(char *word, char **join, int *i);
void			join_var_and_d_quotes(char **join, char *expanded_var);
char			*first_dollars(char *subword, int *i);
void			pass_spaces(char *word, char **join, int *i);

//******** PARS_REDIR_IN ********//
int				merge_value_redir(t_token **head, t_general *general);
int				check_for_dollar(const char *input_string);

/******************************************************************************
*								EXEC										  *
******************************************************************************/

//error.c
int				is_whitespace(char c);
int				check_for_syntax_error(t_token *cmdline, t_general *general);
char			*skip_whitespaces(char *cmdline);
int				deal_with_infile_error(t_general *general);

//builtin_env
char			*get_path(char **envp, char *cmd);
int				create_env_lst(char **envp, t_general *general);
int				convert_env_to_tab(t_general *general);
int				run_env(t_general *general);
int				update_env(t_general *general);
int				deal_with_errors(char *arg_i, bool *error);

//builtin_exit.c
int				run_exit(char **cmd, t_general *general);

//builtin_cd.c
int				run_cd(char **cmd, t_general *general);
char			*get_value_in_env(char *var_name, char **env_tab);

//builtin_echo.c
int				respects_n_format(char *str);
int				run_echo(char **args);

//builtin_unset.c
int				can_be_unset(char *var, char *node_content);
void			remove_from_env(char *var, t_list **env_lst);
int				run_unset(char **args, t_general *general);

//exit_utils.c
int				set_error_true(bool *error);
void			deal_with_minus_sign(int *n, int *i);

//signal.c
void			set_signals_main(void);
void			set_signals_child(void);
void			set_signals_heredoc(void);

//builtin_export
void			print_export(char **dup_env);
void			sort_and_print(char **env_tab);
int				check_valid_identifier(char *str);
size_t			len_until_equal_sign(char *str);
int				add_to_env(t_general *general,
					char *var_and_value, int concatenate);
int				check_for_plus_sign(char *str);
int				is_not_underscore(char *str);
int				run_export(char **args, t_general *general);

//run_builtin.c
int				is_builtin(char *command);
int				run_builtin(t_cmd *cmd_i, t_general *general);

//free.c
void			ft_free_all_but_env(t_general *general);
void			ft_free_env(t_general *general);
void			ft_free_inside_all_cmds(t_general *general);

//exec.c
int				execute_cmd(t_cmd *cmd_i, t_pipe *pipeline,
					t_general *general);
int				execute_cmdline(t_cmd *all_cmds, t_pipe *pipeline,
					t_general *general);

//exec_utils.c
void			exit_builtin_error(int ret, t_general *general);
void			safe_close_remaining_files(t_pipe *pipeline,
					t_general *general);
int				deal_with_binary(char *cmd_path, t_general *general);
void			safe_close_pipefd(t_pipe *pipeline, t_general *general);
int				error_cmd_not_found(char *bad_cmd, t_general *general);

//convert_token_to_tab.c
int				file_exists(char *file_name);
int				ft_nb_of_cmds(t_token *cmdline);
int				ft_len_of_cmd(t_token *token);

//forks_utils.c
int				decode(int child_status);
int				wait_children(int last_pid);
pid_t			safe_fork(t_general *general);

//general_utils.c
void			exit_failure_and_free(t_general *general);

//minishell.c
void			update_nextpipe(t_general *general, t_pipe *pipeline,
					t_cmd *cmd_i, int is_last_cmd);
void			update_prevpipe(t_general *general, t_pipe *pipeline,
					t_cmd *cmd_i, int is_first_cmd);
int				minishell(t_general *general);
void			create_std_backups(t_pipe *pipeline, t_general *general);
void			ft_free_all_but_env(t_general *general);
int				wait_children(int last_pid);

//exec_one_cmd.c
int				redirect_single_cmd_io(t_cmd *cmd,
					t_pipe *pipeline, t_general *general);
int				restore_single_cmd_io(t_cmd *cmd,
					t_pipe *pipeline, t_general *general);
int				execute_one_cmd(t_cmd *all_cmds,
					t_pipe *pipeline, t_general *general);
int				contains_type_out_or_append(char **redir,
					t_token_types *redir_type);
int				contains_type_redir_in(char **redir,
					t_token_types *redir_type);
// int				contains_type_heredoc(char **redir,
// 					t_token_types *redir_type);

//redirections.c
int				open_all_files(t_general *general,
					t_cmd *cmd, char **redir, t_token_types *redir_type);
void			redirect_io_files(t_cmd *cmd_i, int index,
					int nb_of_children, t_general *general);
void			redirect_io(t_general *general, t_pipe *pipeline, t_cmd *cmd);
int				must_close_previous_file(char **redir,
					enum token_types *redir_type, int i);

//test_call_exec.c
int				ft_nb_of_cmds(t_token *cmdline);
int				ft_nb_of_pipes(t_token *token);
int				ft_len_of_cmd(t_token *token);
int				ft_nb_of_redirs_in(t_token *token);
int				ft_nb_of_redirs_out(t_token *token);
int				ft_malloc_cmd_i(t_cmd *all_cmds_i, t_token *token);
int				convert_token_lst_to_tab(t_token *cmdline,
					t_general *general);
void			ft_free_general(t_general *general);

//safe_fd_functions
void			safe_close(int fd, t_general *general);
int				safe_dup(int fd, t_general *general);
int				safe_open_io_files(char *file,
					t_token_types flag, t_general *general);
int				safe_open_heredoc(char *delimiter, t_general *general);

//heredoc.c
int				launch_heredoc(char *delimiter, t_general *general);

//error.c
int				print_error(char *s1, char *s2, char *s3, char *message);

//tools.c
char			*ft_substr(char const *s, unsigned int start, size_t len);

#endif
