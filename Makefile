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
			server/src/utils/get_max_fd.c	\
			server/src/data_transfer/data_work/data_read_packet.c	\
			server/src/write_server.c	\
			server/src/commands/login/login.c	\
			server/src/commands/logout/logout.c	\
			server/src/commands/create/create.c	\
			server/src/commands/create/create_channel.c	\
			server/src/commands/create/create_team.c	\
			server/src/commands/create/create_thread.c	\
			server/src/commands/use/use.c	\
			server/src/commands/use/use_team.c	\
			server/src/data_save/save_team.c	\
			server/src/data_save/load_user.c	\
			server/src/data_save/load_team.c	\
			server/src/data_save/load_thread.c	\
			server/src/data_save/load_comment.c	\
			server/src/data_save/load_channel.c	\
			server/src/data_save/load_team_data.c	\
			server/src/commands/create/create_comment.c

SRC_CLIENT	=	client/src/main.c	\
			client/src/utils/take_port.c	\
			client/src/connection/connect_client.c	\
			client/src/parsing/main_parsing.c	\
			client/src/utils/parsing_utils.c	\
			client/src/commands/create.c	\
			client/src/commands/login.c	\
			client/src/commands/logout.c	\
			client/src/commands/messages.c	\
			client/src/commands/send.c	\
			client/src/commands/subscribe.c	\
			client/src/commands/subscribed.c	\
			client/src/commands/unsubscribe.c	\
			client/src/commands/use.c	\
			client/src/commands/user.c	\
			client/src/commands/users.c	\
			client/src/call_function.c	\
			client/src/select_client.c	\
			client/src/read_server.c	\
			client/src/write_server.c	\
			client/src/server_commands/channel_print_threads.c \
			client/src/server_commands/error_already_exist.c \
			client/src/server_commands/error_unauthorized.c	\
			client/src/server_commands/error_unk_channel.c	\
			client/src/server_commands/error_unk_team.c	\
			client/src/server_commands/error_unk_thread.c	\
			client/src/server_commands/error_unk_user.c	\
			client/src/server_commands/event_channel_created.c \
			client/src/server_commands/event_loggedin.c	\
			client/src/server_commands/event_loggedout.c	\
			client/src/server_commands/event_pv_mes_rx.c	\
			client/src/server_commands/event_team_created.c	\
			client/src/server_commands/event_th_mes_rx.c	\
			client/src/server_commands/event_thread_created.c \
			client/src/server_commands/print_channel.c	\
			client/src/server_commands/print_channel_created.c \
			client/src/server_commands/print_client_subscribed.c \
			client/src/server_commands/print_client_unsubscribed.c\
			client/src/server_commands/print_reply_created.c \
			client/src/server_commands/print_team.c	\
			client/src/server_commands/print_team_created.c	\
			client/src/server_commands/print_teams.c \
			client/src/server_commands/print_thread.c \
			client/src/server_commands/print_thread_created.c \
			client/src/server_commands/print_user.c	\
			client/src/server_commands/print_users.c \
			client/src/server_commands/pv_msg_print_msg.c \
			client/src/server_commands/team_print_channels.c \
			client/src/server_commands/thread_print_replies.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

CFLAGS  += -W -Wall -Wextra -pedantic -ansi -std=gnu11

all:    $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER):	CFLAGS += -I server/include
$(NAME_SERVER): $(OBJ_SERVER)
	gcc -o $(NAME_SERVER) $(OBJ_SERVER) -Llibs/myteams -lmyteams -luuid

$(NAME_CLIENT):	CFLAGS += -I client/include
$(NAME_CLIENT): $(OBJ_CLIENT)
	gcc -o $(NAME_CLIENT) $(OBJ_CLIENT) -Llibs/myteams -lmyteams -luuid

debug:  CFLAGS += -g
debug:  all

debugre:    CFLAGS += -g
debugre:    re

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all
