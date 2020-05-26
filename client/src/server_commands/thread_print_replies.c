/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void thread_print_replies(struct packet_server_s packet, struct client_s *cli)
{
    client_thread_print_replies(packet.thread_id, packet.user_id,
        packet.time_stamp, packet.body);
    (void)packet;
    (void)cli;
}