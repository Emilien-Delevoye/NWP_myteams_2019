/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <unistd.h>
#include <stdlib.h>

static void write_to_client(struct client_s *cur)
{
    struct write_data_s *data = cur->to_write;

    if (write(cur->client_sckt, data->packet, BF_S) != BF_S)
        return;
    cur->to_write = data->next;
    free(data);
}

void write_data(data_server_t *data)
{
    for (struct client_s *cur = data->l_clients; cur; cur = cur->next)
        if (FD_ISSET(cur->client_sckt, &data->sckt_w) &&
            cur->to_write != NULL) {
            write_to_client(cur);
        }
}