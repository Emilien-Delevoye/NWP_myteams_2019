/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#ifndef MYTEAMS_CLIENT_H
#define MYTEAMS_CLIENT_H

#include <stdbool.h>

//Functions
int take_port(char const *port_str);
int connect_client(const char *ip, int port);
char **parsing(char *buffer);

bool not_valid_command(const char *buf);
int get_nb_arg(const char *buffer);
char *get_cmd(char **buffer);
char *get_arg(char **buffer);
void free_cmd(char **cmd);

//Structures
struct client_s {
    int sckt;
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

#endif
