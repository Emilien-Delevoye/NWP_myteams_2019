/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void print_reply_created(struct packet_server_s packet, struct client_s *cli)
{
    client_print_reply_created(packet.thread_id, packet.user_id,
        packet.time_stamp, packet.body);
    (void)cli;
}