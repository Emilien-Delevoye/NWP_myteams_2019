/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

static void add_new_client(data_server_t *data, int new_fd)
{
    struct client_s *n_client = malloc(sizeof(struct client_s));
    struct client_s *current = data->list_clients;

    if (!n_client) {
        printf("malloc: %s\n", strerror(errno));
        close(new_fd);
        return;
    }
    n_client->next = NULL;
    n_client->client_sckt = new_fd;
    if (!data->list_clients) {
        data->list_clients = n_client;
    } else {
        while (current->next)
            current = current->next;
        current->next = n_client;
    }
}

void accept_connections(data_server_t *data)
{
    int new_fd;

    if (!FD_ISSET(data->control_sckt, &data->sckt_pannel[R_FD]))
        return;
    new_fd = accept(data->control_sckt, NULL, 0);
    if (new_fd < 0) {
        printf("accept: %s\n", strerror(errno));
        return;
    }
    add_new_client(data, new_fd);
}