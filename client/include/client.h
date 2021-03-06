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
void list(struct client_s *client, char **command);
void info(struct client_s *client, char **command);

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

struct packet_server_s {
    unsigned short command;
    char team_id[LUID];
    char channel_id[LUID];
    char thread_id[LUID];
    char user_id[LUID];
    char name[33];
    char description[256];
    char body[513];
    int user_status;
    time_t time_stamp;
    unsigned char broadcast;
} __attribute__((packed));

/* *** RX Server functions *** */
void event_loggedin(struct packet_server_s, struct client_s *);
void event_loggedout(struct packet_server_s, struct client_s *);
void event_pv_mes_rx(struct packet_server_s, struct client_s *);
void event_th_mes_rx(struct packet_server_s, struct client_s *);
void event_team_created(struct packet_server_s, struct client_s *);
void event_channel_created(struct packet_server_s, struct client_s *);
void event_thread_created(struct packet_server_s, struct client_s *);
void print_users(struct packet_server_s, struct client_s *);
void print_teams(struct packet_server_s, struct client_s *);
void team_print_channels(struct packet_server_s, struct client_s *);
void channel_print_threads(struct packet_server_s, struct client_s *);
void thread_print_replies(struct packet_server_s, struct client_s *);
void pv_msg_print_msg(struct packet_server_s, struct client_s *);
void error_unk_team(struct packet_server_s, struct client_s *);
void error_unk_channel(struct packet_server_s, struct client_s *);
void error_unk_thread(struct packet_server_s, struct client_s *);
void error_unk_user(struct packet_server_s, struct client_s *);
void error_unauthorized(struct packet_server_s, struct client_s *);
void error_already_exist(struct packet_server_s, struct client_s *);
void print_user(struct packet_server_s, struct client_s *);
void print_team(struct packet_server_s, struct client_s *);
void print_channel(struct packet_server_s, struct client_s *);
void print_thread(struct packet_server_s, struct client_s *);
void print_team_created(struct packet_server_s, struct client_s *);
void print_channel_created(struct packet_server_s, struct client_s *);
void print_thread_created(struct packet_server_s, struct client_s *);
void print_reply_created(struct packet_server_s, struct client_s *);
void print_client_subscribed(struct packet_server_s, struct client_s *);
void print_client_unsubscribed(struct packet_server_s, struct client_s *);

/* *** Lib commands *** */

int client_event_loggedin(char const *user_id, const char *user_name); //1
int client_event_loggedout(char const *user_id, const char *user_name); //2
int client_event_private_message_received(char const *user_id,
    char const *message_body); //3
int client_event_thread_message_received(char const *team_id,
    char const *thread_id, char const *user_id, char const *message); //4
int client_event_team_created(char const *team_id, char const *team_name,
    char const *team_description); //5
int client_event_channel_created(char const *channel_id,
    char const *channel_name, char const *channel_description); //6
int client_event_thread_created(char const *thread_id, char const *user_id,
    time_t thread_timestamp, char const *thread_title,
    char const *thread_body); //7
int client_print_users(char const *user_id, char const *user_name,
    int user_status); //8
int client_print_teams(char const *team_id, char const *team_name,
    char const *team_description); //9
int client_team_print_channels(char const *channel_id,
    char const *channel_name, char const *channel_description); //10
int client_channel_print_threads(char const *thread_id, char const *user_id,
    time_t thread_timestamp, char const *thread_title,
    char const *thread_body); //11
int client_thread_print_replies(char const *thread_id, char const *user_id,
    time_t reply_timestamp, char const *reply_body); //12
int client_private_message_print_messages(char const *sender_id,
    time_t timestamp, char const *message); //13
int client_error_unknown_team(char const *team_id); //14
int client_error_unknown_channel(char const *channel_id); //15
int client_error_unknown_thread(char const *thread_id); //16
int client_error_unknown_user(char const *user_id); //17
int client_error_unauthorized(void); //18
int client_error_already_exist(void); //19
int client_print_user(char const *user_id, char const *user_name,
    int user_status); //20
int client_print_team(char const *team_id, char const *team_name,
    char const *team_description); //21
int client_print_channel(char const *channel_id, char const *channel_name,
    char const *channel_description); //22
int client_print_thread(char const *thread_id, char const *user_id,
    time_t thread_timestamp, char const *thread_title,
    char const *thread_body); //23
int client_print_team_created(char const *team_id, char const *team_name,
    char const *team_description); //24
int client_print_channel_created(char const *channel_id,
    char const *channel_name, char const *channel_description); //25
int client_print_thread_created(char const *thread_id, char const *user_id,
    time_t thread_timestamp, char const *thread_title,
    char const *thread_body); //26
int client_print_reply_created(char const *thread_id,
    char const *user_id, time_t reply_timestamp, char const *reply_body); //27
int client_print_subscribed(char const *user_id, char const *team_id); //28
int client_print_unsubscribed(char const *user_id, char const *team_id); //29

#endif
