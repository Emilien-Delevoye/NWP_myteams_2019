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

static void add_broadcast(data_server_t *data, struct write_data_s *cur)
{
    struct write_data_s *to_write;

    for (struct client_s *act = data->l_clients; act; act = act->next) {
        to_write = malloc(sizeof(struct write_data_s));
        if (!to_write)
            return;
        add_to_buffer_list(act, cur->packet);
    }
}

void write_data(data_server_t *data)
{
    struct write_data_s *act;

    while (data->broadcast) {
        add_broadcast(data, data->broadcast);
        act = data->broadcast;
        data->broadcast = data->broadcast->next;
        free(act);
    }
    for (struct client_s *cur = data->l_clients; cur; cur = cur->next) {
        if (FD_ISSET(cur->client_sckt, &data->sckt_w) &&
            cur->to_write != NULL) {
            write_to_client(cur);
        }
    }
}