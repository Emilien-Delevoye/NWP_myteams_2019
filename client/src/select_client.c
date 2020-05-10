/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <unistd.h>

void define_fd_set(struct client_s *client)
{
    FD_ZERO(&client->fd_rd);
    FD_ZERO(&client->fd_wr);
    FD_SET(0, &client->fd_rd);
    FD_SET(client->sckt, &client->fd_rd);
    FD_SET(client->sckt, &client->fd_wr);
}

void read_af_select(struct client_s *client)
{
    if (FD_ISSET(0, &client->fd_rd))
        read_input(client);
    if (FD_ISSET(client->sckt, &client->fd_rd))
        read_server(client);
    if (FD_ISSET(client->sckt, &client->fd_wr) && client->to_write)
        write_server(client);
}

int select_client(struct client_s *cli)
{
    int s_v;

    define_fd_set(cli);
    s_v = select(cli->sckt + 1, &cli->fd_rd, &cli->fd_wr, NULL, NULL);
    if (s_v < 0)
        return (-1);
    read_af_select(cli);
    if (cli->server_running == false)
        return (0);
    return (1);
}