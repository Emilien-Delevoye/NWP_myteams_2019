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
    data_server_t data = {.control_sckt = init_ctr_socket(port),
        .list_clients = NULL, .get_max_fd = get_max_fd_fct};

    load_data(&data);
    if (port < 0 || data.control_sckt < 0 || setup_sigcatch() < 0)
        return (84);
    while (server_running()) {
        setup_fd_set(&data);
        if (select_fd(data) < 0)
            break;
        accept_connections(&data);
        write_data(data);
        read_data(data);
    }
    close_connections(data);
    save_data(data);
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