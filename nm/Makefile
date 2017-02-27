##
## Makefile for make in /nm/
##
## Made by Frederic ODDOU
## Login   <frederic.oddou@epitech.eu>
##
## Started on  Mon Feb 13 14:09:31 2017 Frederic ODDOU
## Last update Sun Feb 26 23:28:15 2017 Fredoddou
##

ECHO	=	/bin/echo -e
DEFAULT	=	"\033[00m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[1;36m"
RED	=	"\033[0;31m"
BLUE	=	"\033[0;34m"

DIR_INC =	./include/
DIR_SRC =	./src/
DIR_64  =	$(DIR_SRC)64bits/
DIR_32  =	$(DIR_SRC)32bits/

SRC 	=	$(DIR_SRC)main.c \
		$(DIR_SRC)parser.c \
		$(DIR_SRC)check_file.c \
		$(DIR_SRC)exec_nm.c \
		$(DIR_SRC)sort.c \
		$(DIR_SRC)display.c \
		$(DIR_SRC)tools.c \
		$(DIR_SRC)open_ar_file.c \
		$(DIR_64)get_sym64.c \
		$(DIR_32)get_sym32.c \
		$(DIR_64)exec_nm64.c \
		$(DIR_32)exec_nm32.c

OBJ	=	$(SRC:.c=.o)

CC	=	gcc

RM	=	rm -f

CFLAGS	+=	-Wextra \
		-Wall \
		-Werror \
		-I$(DIR_INC)

LDFLAGS	=

NAME	=	./../my_nm

all:		$(NAME)

$(NAME):	$(OBJ)
		@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
		@$(RM) $(OBJ)

fclean:		clean
		@$(RM) $(NAME)

re:		fclean all

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		$(ECHO) $(GREEN) "[OK]" $(TEAL) $< $(DEFAULT) || \
		$(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)

.PHONY:		all clean fclean re $(NAME) .c.o
