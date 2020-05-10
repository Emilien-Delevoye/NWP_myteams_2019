/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <unistd.h>
#include <stdlib.h>

void write_server(struct client_s *client)
{
    struct write_data_s *to_write = client->to_write;
    int len_wr;

    len_wr = write(client->sckt, to_write->packet, sizeof(to_write->packet));
    if (len_wr != 4096)
        return;
    client->to_write = to_write->next;
    free(to_write);
}