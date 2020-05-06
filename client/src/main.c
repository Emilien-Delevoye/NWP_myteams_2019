/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <stdio.h>
#include <unistd.h>

void help(void)
{
    puts("USAGE: ./myteams_cli ip port\n\t"
        "ip\tis the server ip address on which the server socket listens\n\t"
        "port\tis the port number on which the server socket listens\n");
}

int client(const char *ip, int port)
{
    struct client_s client;

    client.sckt = connect_client(ip, port);
    if (client.sckt < 0)
        return (84);
    sleep(4);
    close(client.sckt);
    return (0);
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