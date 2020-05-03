/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>

void help(void)
{
    puts("USAGE: ./myteams_server port\n"
         "\tport\tis the port number on which the server socket listens.\n");
}

int server(char *port_str)
{
    int port = take_port(port_str);
    int sckfd = init_ctr_socket(port);

    if (port < 0 || sckfd < 0)
        return (84);
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        help();
        return (84);
    }
    return (server(av[1]));
}