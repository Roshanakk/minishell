#include "src/main.h"

typedef enum s_type
{
    WORD,
    CMD,
    ARG,
    VAR,
    PIPE,
    HEREDOC,
    REDIR_INPUT,
    REDIR_OUTPUT,
    APPEND
}    t_type;

typedef struct s_token
{
    char        *value;
    t_type        type;
    t_token        *next;
} t_token;

typedef struct s_general
{
    t_list        **env;
    char        **new_env;
    char        ***address_envp;
    int            env_ignored;
    int            fd_tmp;
    t_command    *all_cmds;
    t_pipe        *pipeline;
    t_token        **cmdline;
}    t_general;

typedef struct s_pipe
{
    int            pipes;
    int            fd[2];
    int            prev_pipe;
    __pid_t        *pid;
    t_general    *all;
    t_token        **cmdline;
}    t_pipe;

typedef struct s_command
{
    char    **cmd_args;
    t_token    *redirections;
    int        here_fd[2];
}    t_command;