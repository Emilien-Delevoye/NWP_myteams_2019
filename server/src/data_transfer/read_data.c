/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <unistd.h>
#include <stdio.h>

static void read_client(data_server_t *data, struct client_s *cur)
{
    char buffer[4096] = {0};

    read(cur->client_sckt, buffer, sizeof(buffer));
    puts(buffer);
}

void read_data(data_server_t *data, fd_set *read_pannel)
{
    for (struct client_s *cur = data->list_clients; cur; cur = cur->next) {
        if (FD_ISSET(cur->client_sckt, read_pannel))
            read_client(data, cur);
    }
}