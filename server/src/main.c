/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void help(void)
{
    puts("USAGE: ./myteams_server port\n"
        "\tport\tis the port number on which the server socket listens.\n");
}

int server(char *port_str)
{
    int port = take_port(port_str);
    data_server_t data = {.control_sckt = init_ctr_socket(port),
        .l_clients = NULL, .l_teams = NULL, .get_max_fd = get_max_fd_fct,
        .broadcast = NULL};

    if (port < 0 || data.control_sckt < 0 || setup_sigcatch() < 0)
        return (84);
    load_data(&data);
    while (server_running()) {
        setup_fd_set(&data);
        if (select_fd(&data) < 0)
            break;
        accept_connections(&data);
        write_data(&data);
        read_data(&data);
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
    srand(time(NULL));
    return (server(av[1]));
}