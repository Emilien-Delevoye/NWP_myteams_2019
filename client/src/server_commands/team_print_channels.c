/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void team_print_channels(struct packet_server_s packet, struct client_s *cli)
{
    client_team_print_channels(packet.channel_id, packet.name,
        packet.description);
    (void)packet;
    (void)cli;
}