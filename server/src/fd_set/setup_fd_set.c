/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>

static void setup_write_fd_set(data_server_t *data)
{
    FD_SET(data->control_sckt, &data->sckt_r);
    for (struct client_s *cur = data->list_clients; cur; cur = cur->next) {
        printf("this fd will be set : %d\n", cur->client_sckt);
        FD_SET(cur->client_sckt, &data->sckt_r);
    }
}

void setup_fd_set(data_server_t *data)
{
    FD_ZERO(&data->sckt_r);
    FD_ZERO(&data->sckt_w);
    setup_write_fd_set(data);
}