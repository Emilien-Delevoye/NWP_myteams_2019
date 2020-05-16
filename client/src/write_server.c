/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct write_data_s *get_prev_write(struct client_s *client)
{
    struct write_data_s *cur = client->to_write;

    if (!cur)
        return (NULL);
    while (cur->next)
        cur = cur->next;
    return (cur);
}

void add_to_buffer_list(struct client_s *client, char buffer[BF_S])
{
    struct write_data_s *to_write = malloc(sizeof(struct write_data_s));
    struct write_data_s *prev = get_prev_write(client);

    if (!to_write)
        return;
    memset(to_write->packet, 0, sizeof(to_write->packet));
    strcpy(to_write->packet, buffer);
    to_write->next = NULL;
    if (prev)
        prev->next = to_write;
    else
        client->to_write = to_write;
}

void write_server(struct client_s *client)
{
    struct write_data_s *to_write = client->to_write;
    int len_wr;

    len_wr = write(client->sckt, to_write->packet, sizeof(to_write->packet));
    if (len_wr != BF_S)
        return;
    client->to_write = to_write->next;
    free(to_write);
}