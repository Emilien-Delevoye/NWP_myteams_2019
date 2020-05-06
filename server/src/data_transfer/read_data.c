/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void remove_elem(data_server_t *data, struct client_s *cur,
    struct client_s *pre)
{
    printf("client closed %d\n", cur->client_sckt);
    if (pre == NULL) {
        data->list_clients = cur->next;
        free(cur);
    } else {
        pre->next = cur->next;
        free(cur);
    }
}

static void close_client(struct client_s *to_close)
{
    close(to_close->client_sckt);
    to_close->to_delete = true;
}

static void read_client(data_server_t *data __attribute__((unused)),
    struct client_s *cur)
{
    char buffer[4096] = {0};
    int read_val = read(cur->client_sckt, buffer, sizeof(buffer));

    if (read_val == 0)
        close_client(cur);
    puts(buffer);
}

void read_data(data_server_t *data)
{
    for (struct client_s *cur = data->list_clients; cur; cur = cur->next)
        if (FD_ISSET(cur->client_sckt, &data->sckt_r))
            read_client(data, cur);
}