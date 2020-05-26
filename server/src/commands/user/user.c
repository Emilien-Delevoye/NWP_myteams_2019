/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

void send_unk_user(struct client_s *cli, char *uuid)
{
    struct packet_server_s packet = {0};
    size_t len_uuid = strlen(uuid);
    size_t len_pack = sizeof(packet.user_id);

    packet.command = 17;
    memcpy(packet.user_id, uuid, (len_uuid > len_pack) ? len_pack : len_uuid);
    add_to_buffer_list(cli, packet);
}

void send_user_pack(data_server_t *da, struct client_s *cl, struct user_s *cu)
{
    struct packet_server_s packet = {0};

    packet.command = 20;
    memcpy(packet.user_id, cu->uuid, sizeof(packet.user_id));
    memcpy(packet.name, cu->username, sizeof(packet.name));
    packet.user_status = get_status_user(da, cu);
    add_to_buffer_list(cl, packet);
}

void user(char buffer[BF_S], data_server_t *data, struct client_s *cli)
{
    char *cmd[2] = {strtok(buffer, "|"), strtok(NULL, "|")};
    char uuid[LUID];

    if (!cmd[1])
        return;
    if (strlen(cmd[1]) != 36)
        send_unk_user(cli, cmd[1]);
    strcpy(uuid, cmd[1]);
    for (struct user_s *cur = data->l_users; cur; cur = cur->next) {
        if (strcmp(cur->uuid, uuid) == 0) {
            send_user_pack(data, cli, cur);
            return;
        }
    }
    send_unk_user(cli, uuid);
}