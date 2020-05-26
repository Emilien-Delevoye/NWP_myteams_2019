/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

static void list_sub_by_user(struct client_s *cli)
{
    struct packet_server_s packet = {0};

    if (!cli->user)
        return;
    for (struct list_team_cli_s *cur = cli->user->joined_teams; cur;
        cur = cur->next) {
        packet.command = 9;
        memcpy(packet.team_id, cur->team->uuid, sizeof(packet.team_id));
        memcpy(packet.name, cur->team->name, sizeof(cur->team->name));
        memcpy(packet.description, cur->team->desc, sizeof(cur->team->desc));
        add_to_buffer_list(cli, packet);
    }
}

void subscribed(char buffer[BF_S], data_server_t *data, struct client_s *cli)
{
    char uuid[LUID];

    memcpy(uuid, buffer + 12, sizeof(uuid));
    if (strlen(uuid) != 36)
        list_sub_by_user(cli);
}
