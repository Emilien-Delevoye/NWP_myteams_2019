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
#include <arpa/inet.h>

#define NEWADDR (struct sockaddr *)&new_addr
#define LENADDR (socklen_t *)&len

static void init_client(struct client_s *n_client)
{
    n_client->next = NULL;
    n_client->user = NULL;
    n_client->team = NULL;
    n_client->channel = NULL;
    n_client->thread = NULL;
    n_client->to_write = NULL;
    n_client->to_delete = false;
}

static void send_already_logged_in(struct client_s *client,
    data_server_t *data)
{
    struct packet_server_s packet = {0};

    for (struct client_s *cur = data->l_clients; cur; cur = cur->next) {
        if (!cur->user)
            continue;
        memset(&packet, 0, sizeof(packet));
        memcpy(packet.user_id, cur->user->uuid, sizeof(packet.user_id));
        memcpy(packet.name, cur->user->username, sizeof(packet.name));
        packet.command = 1;
        add_to_buffer_list(client, packet);
    }
}

static void add_new_client(data_server_t *data, int new_fd)
{
    struct client_s *n_client = malloc(sizeof(struct client_s));
    struct client_s *current = data->l_clients;

    if (!n_client) {
        close(new_fd);
        return;
    }
    init_client(n_client);
    n_client->client_sckt = new_fd;
    if (!data->l_clients) {
        data->l_clients = n_client;
    } else {
        while (current->next)
            current = current->next;
        current->next = n_client;
    }
    send_already_logged_in(n_client, data);
}

void accept_connections(data_server_t *data)
{
    struct sockaddr_in new_addr = {0};
    int len = sizeof(new_addr);
    int new_fd;

    if (!FD_ISSET(data->control_sckt, &data->sckt_r))
        return;
    new_fd = accept(data->control_sckt, NEWADDR, LENADDR);
    if (new_fd < 0) {
        return;
    }
    add_new_client(data, new_fd);
}