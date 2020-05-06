/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdio.h>
#include <stdlib.h>

static void remove_free_client(struct client_s *current, struct client_s *prev,
    data_server_t *data)
{
    if (prev == NULL)
        data->list_clients = current->next;
    else
        prev->next = current->next;
    free(current);
}

static int check_to_remove(data_server_t *data)
{
    struct client_s *current = data->list_clients;
    struct client_s *prev = NULL;

    while (current) {
        if (current->to_delete == true) {
            remove_free_client(current, prev, data);
            return (check_to_remove(data));
        }
        prev = current;
        current = current->next;
    }
    return (0);
}

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
    check_to_remove(data);
    FD_ZERO(&data->sckt_r);
    FD_ZERO(&data->sckt_w);
    setup_write_fd_set(data);
}