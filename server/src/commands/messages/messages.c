/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

void messages(char buffer[BF_S], data_server_t *data, struct client_s *cli)
{
    char *cr[2] = {NULL, NULL};
    struct packet_server_s packet = {0};

    cr[0] = strtok(buffer, "|");
    cr[1] = strtok(NULL, "|");
    if (!cr[0] || !cr[1] || strlen(cr[1]) != (LUID - 1))
        return;
    for (struct list_msg_cli_s *cur = cli->user->msg; cur; cur = cur->next) {
        if (strcmp(cur->uuid_sender, cr[1]) == 0) {
            memset(&packet, 0, sizeof(packet));
            packet.command = 13;
            memcpy(packet.user_id, cr[1], LUID - 1);
            memcpy(packet.body, cur->msg, sizeof(packet.body));
            packet.time_stamp = cur->timestamp;
            add_to_buffer_list(cli, packet);
        }
    }
}