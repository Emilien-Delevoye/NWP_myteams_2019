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
			server/src/control_socket/init_control_socket.c	\
			server/src/utils/server_running.c	\
			server/src/fd_set/select_fd.c	\
			server/src/fd_set/setup_fd_set.c	\
			server/src/data_transfer/read_data.c	\
			server/src/data_transfer/write_data.c	\
			server/src/utils/close_connections.c	\
			server/src/data_save/load_data.c	\
			server/src/data_save/save_data.c	\
			server/src/control_socket/accept_connections.c	\
			server/src/utils/get_max_fd.c

SRC_CLIENT	=	client/src/main.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

CFLAGS  += -W -Wall -Wextra -pedantic -ansi -std=gnu11

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
