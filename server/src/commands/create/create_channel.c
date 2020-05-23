/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

bool existing_channel(char *name, struct channel_s *list, struct client_s *cli)
{
    struct packet_server_s packet = {0};

    if (!list)
        return (false);
    while (list) {
        if (strcmp(name, list->name) == 0) {
            packet.command = 19;
            add_to_buffer_list(cli, packet);
            return (true);
        }
        list = list->next;
    }
    return (false);
}

static void ping_client_n_channel(struct channel_s *new, struct client_s *cli)
{
    struct packet_server_s packet = {0};

    packet.command = 6;
    memcpy(packet.channel_id, new->uuid, sizeof(new->uuid));
    memcpy(packet.name, new->name, sizeof(new->name));
    memcpy(packet.description, new->desc, sizeof(new->desc));
    add_to_buffer_list(cli, packet);
}

void init_channel(char *n[3], struct channel_s *new,
    struct client_s *cli)
{
    size_t len_1 = strlen(n[1]);
    size_t len_2 = strlen(n[2]);
    uuid_t uuid;

    memset(new, 0, sizeof(struct channel_s));
    strncpy(new->name, n[1], (len_1 > 32 ? 32 : len_1));
    strncpy(new->desc, n[2], (len_2 > 255 ? 255 : len_2));
    uuid_generate_random(uuid);
    uuid_unparse(uuid, new->uuid);
    server_event_channel_created(U_TC cli->team->uuid, U_TC new->uuid,
        new->name);
    ping_client_n_channel(new, cli);
    new->next = NULL;
}