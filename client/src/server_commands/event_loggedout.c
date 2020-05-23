/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void event_loggedout(struct packet_server_s packet, struct client_s *cli)
{
    client_event_loggedout(packet.user_id, packet.name);
    if (packet.broadcast == 0)
        cli->server_running = false;
}