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
    int fd = init_ctr_socket(port);
    data_server_t data = {.control_sckt = fd, .list_clients = NULL,
        .get_max_fd = get_max_fd_fct};
    fd_set read_pannel;

    load_data(&data);
    if (port < 0 || data.control_sckt < 0 || setup_sigcatch() < 0)
        return (84);
    while (server_running()) {
        setup_fd_set(&data, &read_pannel);
        if (select_fd(data, &read_pannel) < 0)
            break;
        accept_connections(&data, &read_pannel);
        write_data(data);
        read_data(&data, &read_pannel);
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