
NAME = minishell

CC = clang

#MODIF ICI ?
CFLAGS = -g3 -Wall -Werror -Wextra -I./libft/src -I./include 

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

SRC = exec/safe_fd_functions.c \
	exec/builtins/builtin_env.c \
	exec/builtins/run_builtin.c \
	exec/builtins/builtin_cd.c \
	exec/builtins/builtin_echo.c \
	exec/builtins/builtin_export.c \
	exec/builtins/builtin_unset.c \
	exec/builtins/builtin_exit.c \
	exec/builtins/exit_utils.c \
	exec/builtins/export_utils.c \
	exec/builtins/export_error_utils.c \
	exec/convert_token_to_tab.c \
	exec/convert_token_to_tab_utils.c \
	exec/error.c \
	exec/exec.c \
	exec/exec_utils.c \
	exec/exec_one_cmd.c \
	exec/minishell.c \
	exec/redirections.c \
	exec/redirections_single_cmd.c \
	exec/redir_utils.c \
	exec/forks_utils.c \
	exec/general_utils.c \
	lexer/token_lst_utils.c \
	lexer/token_utils.c \
	lexer/tokenization.c \
	lexer/tools.c \
	heredoc.c \
	free.c \
	main_error.c \
	parsing/check.c \
	parsing/pars_redir_in.c \
	parsing/pars_append.c \
	parsing/pars_heredoc.c \
	parsing/replace_word_value.c \
	parsing/pars_var.c \
	parsing/pars_var_utils.c \
	parsing/pars_var_utils_2.c \
	expansion/quotes.c \
	expansion/quotes_utils.c \
	signal_main.c \
	signal_child.c \
	signal_heredoc.c \
	main.c	\

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ = ${SRC:.c=.o}
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH) -I $(LIBFT_PATH)

LIBFT_PATH = ./libft/
LIBFT = ./libft/libft.a

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/exec
	mkdir -p $(OBJ_PATH)/exec/builtins
	mkdir -p $(OBJ_PATH)/lexer
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/expansion

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o $@ $(INC) $(LIBFT) -l readline

$(LIBFT):
	make -C $(LIBFT_PATH)

clean :
	rm -rf ${OBJ_PATH}
	make -C $(LIBFT_PATH) clean

fclean : clean
		rm -f ${NAME} 
		make -C $(LIBFT_PATH) fclean

re : fclean all

.PHONY: re fclean clean all



# NAME = minishell

# SRC = exec/pipex_main.c \
# 	exec/pipex_create_structs.c \
# 	exec/pipex_free.c \
# 	exec/safe_fd_functions.c \
# 	exec/builtin_env.c \
# 	exec/builtin_echo.c \
# 	exec/builtin_export.c \
# 	exec/builtin_unset.c \
# 	exec/builtin_exit.c \
# 	exec/test_call_exec.c \
# 	exec/lst_token.c \
# 	exec/minishell.c \
# 	exec/redirections.c \
# 	lexer/token_lst_utils.c \
# 	lexer/token_utils.c \
# 	lexer/tokens.c \
# 	lexer/tools.c \

# OBJ = ${SRC:.c=.o}

# SRC_PATH = ./src
# OBJ_PATH = ./obj

# OBJ_FILES = $(addprefix $(OBJ_PATH)/,$(OBJ))
# # %.o: %.c
# # 	${CC} ${CFLAGS} $< -o $@

# CC = gcc

# DEBUG = -fsanitize=address,leak

# # CFLAGS = -Wall -Wextra -Werror -g3 -I./libft
# CFLAGS = -g3 -I./libft/src -I./include

# all : obj ${NAME}

# $(OBJ_PATH) :
# 	mkdir -p $(OBJ_PATH)
# 	mkdir -p $(OBJ_PATH)/exec
# 	mkdir -p $(OBJ_PATH)/lexer

# ${NAME}: ${OBJ_FILES}
# 	make -C libft
# 	${CC} ${CFLAGS} ${OBJ_FILES} -o ${NAME} libft/libft.a

# $(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
# 	${CC} ${CFLAGS} -c $< -o $@

# %.o : %.c
# 	${CC} ${CFLAGS} -o $@ -c $<

# clean :
# 	rm -rf ${OBJ_PATH}
# 	make -C libft clean

# fclean : clean
# 		rm -f ${NAME} *.a
# 		make -C libft fclean

# re : fclean all

# .PHONY: re fclean clean all
