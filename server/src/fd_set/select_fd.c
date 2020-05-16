/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <errno.h>

int select_fd(data_server_t *data)
{
    if (select(get_max_fd_fct(*data), &data->sckt_r,
        &data->sckt_w, NULL, NULL) < 0) {
        if (errno == EINTR)
            puts(BLINK YELLOW"\r[STOP] Server will shutdown."DEFAULT);
        else
            puts(RED"An unexpected error occurs"DEFAULT);
        return (-1);
    }
    return (0);
}