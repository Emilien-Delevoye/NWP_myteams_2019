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


/* *** Pre-structure def *** */
struct user_s;
struct client_s;
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


/* *** Structures definition *** */

struct client_s {
    int client_sckt;
    struct user_s *user;
    struct client_s *next;
    bool to_delete;
};

struct user_s {
    char *username;
    uuid_t uuid;
};

typedef struct data_server_s {
    int control_sckt;
    fd_set sckt_r;
    fd_set sckt_w;
    struct client_s *list_clients;
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
