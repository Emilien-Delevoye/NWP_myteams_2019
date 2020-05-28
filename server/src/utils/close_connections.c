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

void close_connections(data_server_t data)
{
    struct client_s *current = data.l_clients;
    struct client_s *to_free;

    for (struct client_s *cur = data.l_clients; cur; cur = cur->next) {
        close(cur->client_sckt);
    }
    while (current) {
        to_free = current;
        current = current->next;
        free(to_free);
    }
    close(data.control_sckt);
}