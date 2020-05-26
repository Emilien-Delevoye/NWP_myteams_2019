/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void channel_print_threads(struct packet_server_s packet, struct client_s *cli)
{
    client_channel_print_threads(packet.thread_id, packet.user_id,
        packet.time_stamp, packet.name, packet.body);
    (void)packet;
    (void)cli;
}
