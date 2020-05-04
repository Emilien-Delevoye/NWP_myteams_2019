/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"

static void setup_write_fd_set(data_server_t *data)
{
    FD_SET(data->control_sckt, &data->sckt_pannel[R_FD]);
}

void setup_fd_set(data_server_t *data)
{
    FD_ZERO(&data->sckt_pannel[R_FD]);
    FD_ZERO(&data->sckt_pannel[W_FD]);

    setup_write_fd_set(data);
}