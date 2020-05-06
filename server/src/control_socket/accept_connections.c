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
#include <netinet/in.h>

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
    n_client->user = NULL;
    n_client->client_sckt = new_fd;
    if (!data->list_clients) {
        data->list_clients = n_client;
    } else {
        while (current->next)
            current = current->next;
        current->next = n_client;
    }
}

void accept_connections(data_server_t *data, fd_set *read_pannel)
{
    struct sockaddr_in new_addr = {0};
    int len = sizeof(new_addr);
    int new_fd;

    if (!FD_ISSET(data->control_sckt, read_pannel))
        return;
    printf("avant le accept %d\n", data->control_sckt);
    new_fd = accept(data->control_sckt, (struct sockaddr *)&new_addr, (socklen_t *)&len);
    write(new_fd, "Bonjour\r\n\0", 10);
    printf("accept: %s\n", strerror(errno));
    printf("New connection on port : %d\n", htonl(new_addr.sin_port));
    printf("après le accept %d (new fd : %d)\n", data->control_sckt, new_fd);
    if (new_fd < 0) {
        printf("accept: %s\n", strerror(errno));
        return;
    }
    add_new_client(data, new_fd);
}