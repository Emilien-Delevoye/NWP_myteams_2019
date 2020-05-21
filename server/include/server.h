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
#define LUID 36

/* *** Pre-structure def *** */
struct user_s;
struct client_s;
struct channel_s;
struct team_s;
typedef struct data_server_s data_server_t;


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
void add_to_buffer_list(struct client_s *client, char buffer[BF_S]);
void add_to_broadcast_list(data_server_t *, char [BF_S], struct client_s *);

void login(char [BF_S], data_server_t *, struct client_s *);
void logout(char [BF_S], data_server_t *, struct client_s *);
void create(char [BF_S], data_server_t *, struct client_s *);
void use(char [BF_S], data_server_t *, struct client_s *);

void create_log_buffer(char buffer[BF_S], struct user_s *cur, char *cmd);
void init_channel(char *[3], struct channel_s *, struct client_s *);
bool existing_team(char *name, struct team_s *list, struct client_s *cli);
void init_team(char *[3], struct team_s *, struct client_s *, data_server_t *);
/* *** Structures definition *** */

struct write_data_s {
    char packet[BF_S];
    struct client_s *ignore;
    struct write_data_s *next;
};

struct list_team_cli_s {
    struct team_s *team;
    struct list_team_cli_s *next;
};

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

struct user_s {
    char *username;
    char uuid[LUID];
    struct list_team_cli_s *joined_teams; //Liste des teams joined
    struct user_s *next;
};

struct comment_s {
    char body[512];
    struct comment_s *next;
};

struct thread_s {
    char name[32];
    char message[512];
    char uuid[LUID];
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

#endif
