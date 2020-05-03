##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

NAME_SERVER	=	myteams_server
NAME_CLIENT	=	myteams_cli

SRC_SERVER	=	server/src/main.c	\
			server/src/utils/take_port.c	\
			server/src/control_socket/init_control_socket.c

SRC_CLIENT	=	client/src/main.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

CFLAGS  += -W -Wall -Wextra -pedantic -ansi -std=c11

all:    $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):	CFLAGS += -I server/include
$(NAME_SERVER): $(OBJ_SERVER)
	gcc -o $(NAME_SERVER) $(OBJ_SERVER)

$(NAME_SERVER):	CFLAGS += -I client/include
$(NAME_CLIENT): $(OBJ_CLIENT)
	gcc -o $(NAME_CLIENT) $(OBJ_CLIENT)

debug:  CFLAGS += -g
debug:  all

debugre:    CFLAGS += -g
debugre:    re

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all
