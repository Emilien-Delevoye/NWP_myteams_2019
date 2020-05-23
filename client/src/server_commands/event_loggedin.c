/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"
#include <string.h>

void event_loggedin(struct packet_server_s packet, struct client_s *cli)
{
    client_event_loggedin(packet.user_id, packet.name);
    if (packet.broadcast == 0) {
        memcpy(cli->user.username, packet.name, sizeof(packet.name));
        memcpy(cli->user.uuid, packet.user_id, sizeof(packet.user_id));
    }
}