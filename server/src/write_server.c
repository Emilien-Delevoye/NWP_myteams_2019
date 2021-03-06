/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <string.h>

static struct write_data_s *get_prev_write(struct client_s *client)
{
    struct write_data_s *cur = client->to_write;

    if (!cur)
        return (NULL);
    while (cur->next)
        cur = cur->next;
    return (cur);
}

static struct write_data_s *get_prev_write_brdcast(data_server_t *data)
{
    struct write_data_s *cur = data->broadcast;

    if (!cur)
        return (NULL);
    while (cur->next)
        cur = cur->next;
    return (cur);
}

void add_to_broadcast_list(data_server_t *data, struct packet_server_s pack,
    struct client_s *ignore)
{
    struct write_data_s *to_write = malloc(sizeof(struct write_data_s));
    struct write_data_s *prev = get_prev_write_brdcast(data);

    to_write->packet = pack;
    to_write->next = NULL;
    to_write->ignore = ignore;
    if (prev)
        prev->next = to_write;
    else
        data->broadcast = to_write;
}

void add_to_buffer_list(struct client_s *client, struct packet_server_s pack)
{
    struct write_data_s *to_write = malloc(sizeof(struct write_data_s));
    struct write_data_s *prev = get_prev_write(client);

    if (!to_write)
        return;
    to_write->packet = pack;
    to_write->next = NULL;
    to_write->ignore = NULL;
    if (prev)
        prev->next = to_write;
    else
        client->to_write = to_write;
}
