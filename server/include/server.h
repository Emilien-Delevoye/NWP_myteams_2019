/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#ifndef MYTEAMS_SERVER_H
#define MYTEAMS_SERVER_H

#include <stdbool.h>
#include <sys/select.h>
#include <uuid/uuid.h>
#include <stdio.h>

#define BF_S 2048
#define U_TC (const char *)
#define LUID 37
#define NEWADDR (struct sockaddr *)&new_addr
#define LENADDR (socklen_t *)&len

/* *** Pre-structure def *** */
struct user_s;
struct client_s;
struct comment_s;
struct thread_s;
struct channel_s;
struct team_s;
typedef struct data_server_s data_server_t;
struct packet_server_s;
struct load_data_s;
struct l_save_team_s;

/* *** Function definition *** */
int take_port(char const *);
int init_ctr_socket(int port);
bool server_running(void);
int setup_sigcatch(void);
void setup_fd_set(data_server_t *data);
int select_fd(data_server_t *data);
void accept_connections(data_server_t *data);
void read_data(data_server_t *data);
void write_data(data_server_t *data);
void save_data(data_server_t data);
void close_connections(data_server_t data);
void load_data(data_server_t *data);
int get_max_fd_fct(data_server_t data);
void read_buffer(char buffer[BF_S], data_server_t *data, struct client_s *cur);
void add_to_buffer_list(struct client_s *client, struct packet_server_s pack);
void add_to_broadcast_list(data_server_t *data, struct packet_server_s pack,
    struct client_s *ignore);

void login(char [BF_S], data_server_t *, struct client_s *);
void logout(char [BF_S], data_server_t *, struct client_s *);
void create(char [BF_S], data_server_t *, struct client_s *);
void use(char [BF_S], data_server_t *, struct client_s *);
void subscribe(char [BF_S], data_server_t *, struct client_s *);
void subscribed(char [BF_S], data_server_t *, struct client_s *);
void unsubscribe(char [BF_S], data_server_t *, struct client_s *);
void users(char [BF_S], data_server_t *, struct client_s *);
void user(char [BF_S], data_server_t *, struct client_s *);
void list(char [BF_S], data_server_t *, struct client_s *);
void info(char [BF_S], data_server_t *, struct client_s *);
void send_cmd(char [BF_S], data_server_t *, struct client_s *);
void messages(char [BF_S], data_server_t *, struct client_s *);

void init_team(char *[3], struct team_s *, struct client_s *, data_server_t *);
void init_channel(char *[3], struct channel_s *, struct client_s *,
    data_server_t *);
void init_thread(char *[3], struct thread_s *,
    struct client_s *, data_server_t *);
bool existing_team(char *, struct team_s *, struct client_s *);
bool existing_channel(char *, struct channel_s *, struct client_s *);
bool existing_thread(char *, struct thread_s *, struct client_s *);
void use_team(char *n[2], data_server_t *data, struct client_s *cli);
void save_team(data_server_t, int);
void load_joined_team(int fd, struct load_data_s *load);
void load_user(int fd, struct load_data_s *load_data);
void load_team(int fd, struct load_data_s *load_data);
void load_channel(int fd, struct load_data_s *load_data);
void load_thread(int fd, struct load_data_s *load_data);
void load_comment(int fd, struct load_data_s *load_data);
void load_message(int fd, struct load_data_s *load_data);
void add_team_data(data_server_t *data, struct l_save_team_s team);
void send_comment_packet(struct client_s *cli, struct comment_s *new,
    data_server_t *);
void interpret_cmd(char [BF_S], data_server_t *, struct client_s *);
int get_status_user(data_server_t *, struct user_s *);
void send_unk_team(struct client_s *cli, char *uuid);

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

/* *** Structures definition *** */

struct write_data_s {
    struct packet_server_s packet;
    struct client_s *ignore;
    struct write_data_s *next;
};

typedef struct list_team_cli_s {
    struct team_s *team;
    struct list_team_cli_s *next;
} list_team_cli_t;

struct client_s {
    int client_sckt;
    struct user_s *user;
    struct client_s *next;
    struct write_data_s *to_write;
    struct team_s *team;        //Pointeur vers la team actuellement use
    struct channel_s *channel;  //Pointeur vers le channel actuellement use
    struct thread_s *thread;    //Pointeur vers le thread actuellement use
    bool to_delete;
};

struct list_msg_cli_s {
    char uuid_sender[LUID];
    char msg[513];
    time_t timestamp;
    struct list_msg_cli_s *next;
};

struct user_s {
    char username[33];
    char uuid[LUID];
    struct list_msg_cli_s *msg;
    struct list_team_cli_s *joined_teams; //Liste des teams joined
    struct user_s *next;
};

struct comment_s {
    char body[512];
    char uuid_user[LUID];
    time_t timestamp;
    struct comment_s *next;
};

struct thread_s {
    char name[32];
    char msg[512];
    char uuid[LUID];
    char uuid_user[LUID];
    time_t timestamp;
    struct comment_s *comments;
    struct thread_s *next;
};

struct channel_s {
    char name[32];
    char desc[255];
    char uuid[LUID];
    struct thread_s *threads;
    struct channel_s *next;
};

struct team_s {
    char name[32];
    char desc[255];
    char uuid[LUID];
    struct channel_s *channels;
    struct team_s *next;
};

typedef struct data_server_s {
    fd_set sckt_r;
    fd_set sckt_w;
    int control_sckt;
    struct team_s *l_teams;     //Teams existantes pour le serveur
    struct user_s *l_users;     //Users existants pour le serveur
    struct client_s *l_clients; //Clients connectés au serveur
    struct write_data_s *broadcast; //Liste de broadcast
    int (*get_max_fd)(data_server_t);
} data_server_t;


/* *** Colors *** */
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

/* *** Lib functions *** */

int server_event_team_created(char const *team_id, char const *team_name,
    char const *user_id);
int server_event_channel_created(char const *team_id, char const *channel_id,
    char const *channel_name);
int server_event_thread_created(char const *channel_id, char const *thread_id,
    char const *user_id, char const *message);
int server_event_thread_new_message(char const *thread_id, char const *user_id,
    char const *message);
int server_event_user_join_a_team(char const *team_id, char const *user_id);
int server_event_user_leave_a_team(char const *team_id, char const *user_id);
int server_event_user_created(char const *user_id, char const *user_name);
int server_event_user_loaded(char const *user_id, char const *user_name);
int server_event_user_logged_in(char const *user_id);
int server_event_user_logged_out(char const *user_id);
int server_event_private_message_sended(char const *sender_id,
    char const *receiver_id, char const *message);

/* *** Save and load data *** */

struct save_user_s
{
    char username[33];
    char uuid[LUID];
};

struct joi_team_s
{
    char uuid[LUID];
};

struct save_team_s
{
    char name[33];
    char description[256];
    char uuid[LUID];
};

struct save_channel_s
{
    char name[33];
    char description[256];
    char uuid[LUID];
};

struct save_thread_s
{
    char name[33];
    char msg[513];
    char uuid[LUID];
    char uuid_user[LUID];
    time_t timestamp;
};

struct save_comment_s
{
    char body[513];
    char usr_id[LUID];
    time_t timestamp;
};

struct save_message_s {
    char uuid_send[LUID];
    char message[513];
    time_t timestamp;
};

struct load_data_s {
    struct l_save_user_s *user;
    struct l_save_team_s *team;
    struct l_save_user_s *cur_user;
    struct l_save_team_s *cur_team;
    struct l_save_channel_s *cur_channel;
    struct l_save_thread_s *cur_thread;
};

struct l_messages_s {
    struct save_message_s message;
    struct l_messages_s *next;
};

struct l_joi_team_s {
    struct joi_team_s joined;
    struct l_joi_team_s *next;
};

struct l_save_user_s {
    struct save_user_s user;
    struct l_messages_s *msg;
    struct l_joi_team_s *joined;
    struct l_save_user_s *next;
};

struct l_save_comment_s {
    struct save_comment_s comment;
    struct l_save_comment_s *next;
};

struct l_save_thread_s {
    struct save_thread_s thread;
    struct l_save_comment_s *comments;
    struct l_save_thread_s *next;
};

struct l_save_channel_s {
    struct save_channel_s channel;
    struct l_save_thread_s *threads;
    struct l_save_channel_s *next;
};

struct l_save_team_s {
    struct save_team_s team;
    struct l_save_channel_s *channels;
    struct l_save_team_s *next;
};

#endif
