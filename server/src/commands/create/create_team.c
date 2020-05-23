/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

bool existing_team(char *name, struct team_s *list, struct client_s *cli)
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

static void ping_client_n_team(struct team_s *new, data_server_t *data,
    struct client_s *cli)
{
    struct packet_server_s packet = {0};

    packet.command = 5;
    memcpy(packet.team_id, new->uuid, sizeof(new->uuid));
    memcpy(packet.name, new->name, sizeof(new->name));
    memcpy(packet.description, new->desc, sizeof(new->desc));
    add_to_broadcast_list(data, packet, NULL);
    packet.command = 24;
    add_to_buffer_list(cli, packet);
}

void init_team(char *n[3], struct team_s *new, struct client_s *cli,
    data_server_t *data)
{
    size_t len_1 = strlen(n[1]);
    size_t len_2 = strlen(n[2]);
    uuid_t uuid;

    memset(new, 0, sizeof(struct team_s));
    strncpy(new->name, n[1], (len_1 > 32 ? 32 : len_1));
    strncpy(new->desc, n[2], (len_2 > 255 ? 255 : len_2));
    uuid_generate_random(uuid);
    uuid_unparse(uuid, new->uuid);
    server_event_team_created(new->uuid, new->name, cli->user->uuid);
    ping_client_n_team(new, data, cli);
    new->next = NULL;
}