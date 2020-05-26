/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

int get_status_user(data_server_t *data, struct user_s *cur)
{
    for (struct client_s *cli = data->l_clients; cli; cli = cli->next) {
        if (cli->user == cur)
            return (1);
    }
    return (0);
}

void users(char buffer[BF_S] __attribute__((unused)),
    data_server_t *data, struct client_s *cli)
{
    struct packet_server_s packet = {0};

    for (struct user_s *cur = data->l_users; cur; cur = cur->next) {
        memset(&packet, 0, sizeof(packet));
        packet.command = 8;
        memcpy(&packet.user_id, cur->uuid, sizeof(packet.user_id));
        memcpy(&packet.name, cur->username, sizeof(packet.name));
        packet.user_status = get_status_user(data, cur);
        add_to_buffer_list(cli, packet);
    }
}