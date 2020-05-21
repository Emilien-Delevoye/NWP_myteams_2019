/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#ifndef MYTEAMS_SERVER_H
#define MYTEAMS_SERVER_H

#include "loggin_server.h"
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
void init_team(char *n[3], struct team_s *, struct client_s *);
/* *** Structures definition *** */

struct write_data_s {
    char packet[BF_S];
    struct client_s *ignore;
    struct write_data_s *next;
};

struct client_s {
    int client_sckt;
    struct user_s *user;
    struct client_s *next;
    struct write_data_s *to_write;
    struct team_s *team;
    struct channel_s *channel;
    struct thread_s *thread;
    bool to_delete;
};

struct user_s {
    char *username;
    char uuid[LUID];
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
    struct team_s *l_teams;
    struct client_s *l_clients;
    struct user_s *l_users;
    struct write_data_s *broadcast;
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


#endif
