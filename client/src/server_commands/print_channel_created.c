/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void print_channel_created(struct packet_server_s packet, struct client_s *cli)
{
    client_print_channel_created(packet.channel_id, packet.name,
        packet.description);
    (void)cli;
}