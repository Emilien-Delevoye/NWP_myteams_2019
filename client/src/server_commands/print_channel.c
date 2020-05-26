/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void print_channel(struct packet_server_s packet, struct client_s *cli)
{
    client_print_channel(packet.channel_id, packet.name, packet.description);
    (void)cli;
}