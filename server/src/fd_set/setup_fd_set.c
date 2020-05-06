/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>

static void setup_write_fd_set(data_server_t *data, fd_set *read_pannel)
{
    FD_SET(data->control_sckt, read_pannel);
    for (struct client_s *cur = data->list_clients; cur; cur = cur->next) {
        printf("this fd will be set : %d\n", cur->client_sckt);
        FD_SET(cur->client_sckt, read_pannel);
    }
}

void setup_fd_set(data_server_t *data, fd_set *read_pannel)
{
    FD_ZERO(read_pannel);
    FD_ZERO(&data->sckt_w);
    setup_write_fd_set(data, read_pannel);
}