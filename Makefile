##
## EPITECH PROJECT, 2024
## TCSH
## File description:
## Makefile
##

SRCS	=	src/main.c \
			src/parsing.c \
			src/execution.c \
			src/builtins.c \
			src/env.c \
			src/utils.c \
			src/errors.c \
			src/input.c \
			src/mini_printf.c \
			src/my_str_to_word_array.c \
			src/help.c \
			src/test.c

OBJ 	= 	$(SRCS:.c=.o)

NAME 	=	mysh

all 	: 	$(NAME)

$(NAME) 	:	$(OBJ)
			gcc $(OBJ) -o $(NAME)

clean 	:
		rm -f $(OBJ)

fclean 	: 	clean
		rm -f $(NAME)

re 	: 	fclean all
