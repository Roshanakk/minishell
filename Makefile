NAME = minishell_exec

SRC = pipex_main.c \
	pipex_create_structs.c \
	pipex_free.c \
	safe_fd_functions.c \
	builtin_env.c \
	builtin_echo.c \
	builtin_export.c \
	builtin_unset.c \
	builtin_exit.c \
	test_call_exec.c \
	lst_token.c \
	minishell.c \

OBJ = ${SRC:.c=.o}

SRC_PATH = ./src
OBJ_PATH = ./obj
OBJ_FILES = $(addprefix $(OBJ_PATH)/,$(OBJ))
# %.o: %.c
# 	${CC} ${CFLAGS} $< -o $@

CC = gcc

DEBUG = -fsanitize=address,leak

# CFLAGS = -Wall -Wextra -Werror -g3 -I./libft
CFLAGS = -g3 -I./libft/src

all : obj ${NAME}

obj :
	mkdir -p $(OBJ_PATH)

${NAME}: ${OBJ_FILES}
	make -C libft
	${CC} ${CFLAGS} ${OBJ_FILES} -o ${NAME} libft/libft.a

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	${CC} ${CFLAGS} -c $< -o $@

%.o : %.c
	${CC} ${CFLAGS} -o $@ -c $<

clean :
	rm -rf ${OBJ_PATH}
	make -C libft clean

fclean : clean
		rm -f ${NAME} *.a
		make -C libft fclean

re : fclean all

.PHONY: re fclean clean all