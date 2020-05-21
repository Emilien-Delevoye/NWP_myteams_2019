/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#ifndef MYTEAMS_CLIENT_H
#define MYTEAMS_CLIENT_H

#include <stdbool.h>
#include <sys/select.h>
#include <uuid/uuid.h>
#include <stdio.h>

struct client_s;

#define BF_S 2048
#define LUID 37

//Functions
int take_port(char const *port_str);
int connect_client(const char *ip, int port);
char **parsing(char *buffer);
void call_function(struct client_s *client, char **command);
int select_client(struct client_s *client);
void write_server(struct client_s *client);
void read_input(struct client_s *client);
void read_server(struct client_s *client);

bool not_valid_command(const char *buf);
int get_nb_arg(const char *buffer);
char *get_cmd(char **buffer);
char *get_arg(char **buffer);
void free_cmd(char **cmd);
void add_to_buffer_list(struct client_s *client, char buffer[BF_S]);

void create(struct client_s *client, char **command);
void login(struct client_s *client, char **command);
void logout(struct client_s *client, char **command);
void messages(struct client_s *client, char **command);
void send(struct client_s *client, char **command);
void subscribe(struct client_s *client, char **command);
void subscribed(struct client_s *client, char **command);
void unsubscribe(struct client_s *client, char **command);
void use(struct client_s *client, char **command);
void user(struct client_s *client, char **command);
void users(struct client_s *client, char **command);

void login_server_cli(char [BF_S], struct client_s *);
void logout_server_cli(char [BF_S], struct client_s *);
void create_server_cli(char [BF_S], struct client_s *);

struct write_data_s {
    char packet[BF_S];
    struct write_data_s *next;
};

//Structures

struct user_s {
    char username[32];
    char uuid[LUID];
};

struct client_s {
    int sckt;
    struct user_s user;
    fd_set fd_rd;
    fd_set fd_wr;
    bool server_running;
    struct write_data_s *to_write;
};

#define DOMINIQUE quotes != 0 && quotes % 2 == 0 && buf[a] != ' ' && \
    buf[a] != '\t' && buf[a] != '\n' && buf[a] != '\"'

#define DEFAULT "\033[0m"
#define HIGHLIGHT "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

/* *** Lib commands *** */

int client_event_loggedin(char const *user_id, const char *user_name);
int client_event_loggedout(char const *user_id, const char *user_name);
int client_event_private_message_received(char const *user_id,
    char const *message_body);
int client_event_thread_message_received(char const *team_id,
    char const *thread_id, char const *user_id, char const *message);
int client_event_team_created(char const *team_id, char const *team_name,
    char const *team_description);
int client_event_channel_created(char const *channel_id,
    char const *channel_name, char const *channel_description);
int client_event_thread_created(char const *thread_id, char const *user_id,
    time_t thread_timestamp, char const *thread_title,
    char const *thread_body);
int client_print_users(char const *user_id, char const *user_name,
    int user_status);
int client_print_teams(char const *team_id, char const *team_name,
    char const *team_description);
int client_team_print_channels(char const *channel_id,
    char const *channel_name, char const *channel_description);
int client_channel_print_threads(char const *thread_id, char const *user_id,
    time_t thread_timestamp, char const *thread_title,
    char const *thread_body);
int client_thread_print_replies(char const *thread_id, char const *user_id,
    time_t reply_timestamp, char const *reply_body);
int client_private_message_print_messages(char const *sender_id,
    time_t timestamp, char const *message);
int client_error_unknown_team(char const *team_id);
int client_error_unknown_channel(char const *channel_id);
int client_error_unknown_thread(char const *thread_id);
int client_error_unknown_user(char const *user_id);
int client_error_unauthorized(void);
int client_error_already_exist(void);
int client_print_user(char const *user_id, char const *user_name,
    int user_status);
int client_print_team(char const *team_id, char const *team_name,
    char const *team_description);
int client_print_channel(char const *channel_id, char const *channel_name,
    char const *channel_description);
int client_print_thread(char const *thread_id, char const *user_id,
    time_t thread_timestamp, char const *thread_title,
    char const *thread_body);
int client_print_team_created(char const *team_id, char const *team_name,
    char const *team_description);
int client_print_channel_created(char const *channel_id,
    char const *channel_name, char const *channel_description);
int client_print_thread_created(char const *thread_id, char const *user_id,
    time_t thread_timestamp, char const *thread_title,
    char const *thread_body);
int client_print_reply_created(char const *thread_id,
    char const *user_id, time_t reply_timestamp, char const *reply_body);
int client_print_subscribed(char const *user_id, char const *team_id);
int client_print_unsubscribed(char const *user_id, char const *team_id);

#endif
