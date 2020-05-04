/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <errno.h>

int select_fd(data_server_t data)
{
    if (select(data.control_sckt + 1, &data.sckt_pannel[R_FD],
        &data.sckt_pannel[W_FD], NULL, NULL) < 0) {
        if (errno == EINTR)
            puts("\rServer will shutdown.");
        else
            puts("An unexpected error occurs");
        return (-1);
    }
    return (0);
}