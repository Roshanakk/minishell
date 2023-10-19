NAME = libft.a 

SRC	= ft_printf_utils.c \
	ft_printf.c \
	ft_putnbr_base.c \
	ft_putnbr.c \
	ft_split.c \
	ft_strjoin.c \
	ft_strjoin_and_free.c \
	ft_strdup.c \
	ft_strcmp.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstadd_back.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_array_size.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_swap.c \
	ft_strchr_plus_one.c \

OBJS = ${SRC:.c=.o}

SRC_PATH = ./src
OBJ_PATH = ./obj
SRC_FILES = $(addprefix $(SRC_PATH)/,$(SRC))
OBJ_FILES = $(addprefix $(OBJ_PATH)/,$(OBJS))

CC = cc

CFLAGS = -Wall -Wextra -Werror

all : obj ${NAME}

obj :
	mkdir -p $(OBJ_PATH)

${NAME}: $(OBJ_FILES)
	ar rc ${NAME} ${OBJ_FILES}
	ranlib ${NAME}

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	${CC} ${CFLAGS} -c $< -o $@

%.o : %.c
	${CC} ${CFLAGS} -o $@ -c $<

clean : 
	rm -rf ${OBJ_PATH}

fclean : clean
		rm -f ${NAME} 

re : fclean all

.PHONY: re fclean clean bonus all