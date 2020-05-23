/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

void logout(char buffer[BF_S] __attribute__((unused)), data_server_t *data,
            struct client_s *client)
{
    struct packet_server_s packet = {0};

    if (!client->user)
        return;
    server_event_user_logged_out((const char *)client->user->uuid);
    packet.command = 2;
    memcpy(packet.user_id, client->user->uuid, sizeof(packet.user_id));
    memcpy(packet.name, client->user->username, sizeof(packet.name));
    add_to_buffer_list(client, packet);
    add_to_broadcast_list(data, packet, client);
    client->user = NULL;
}