/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void help(void)
{
    puts("USAGE: ./myteams_cli ip port\n\t"
        "ip\tis the server ip address on which the server socket listens\n\t"
        "port\tis the port number on which the server socket listens\n");
}

int main_loop(struct client_s client)
{
    char *buffer = NULL;
    size_t len = 0;

    while (getline(&buffer, &len, stdin) > 0) {

    }
    free(buffer);
    return (0);
}

int client(const char *ip, int port)
{
    struct client_s client;
    int return_val;

    client.sckt = connect_client(ip, port);
    if (client.sckt < 0)
        return (84);
    return_val = main_loop(client);
    close(client.sckt);
    return (return_val);
}

int main(int ac, char **av)
{
    int port;

    if (ac != 3) {
        help();
        return (84);
    }
    port = take_port(av[2]);
    if (port <= 0)
        return (84);
    return (client(av[1], port));
}