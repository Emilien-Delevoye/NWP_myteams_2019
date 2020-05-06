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
#include <sys/socket.h>

void close_connections(data_server_t data)
{
    struct client_s *current = data.list_clients;
    struct client_s *to_free;

    for (struct client_s *cur = data.list_clients; cur; cur = cur->next)
        shutdown(cur->client_sckt, 2);
    while (current) {
        to_free = current;
        current = current->next;
        free(to_free);
    }
    shutdown(data.control_sckt, 2);
    puts("The server is close");
}