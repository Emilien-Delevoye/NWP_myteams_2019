/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <errno.h>

int select_fd(data_server_t data, fd_set *read_pannel)
{
    //FIXME Changer le data.control_sckt + 1 en get_max_fd
    if (select(get_max_fd_fct(data), read_pannel,
        &data.sckt_w, NULL, NULL) < 0) {
        if (errno == EINTR)
            puts("\rServer will shutdown.");
        else
            puts("An unexpected error occurs");
        return (-1);
    }
    return (0);
}