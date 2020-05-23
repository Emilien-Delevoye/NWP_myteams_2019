/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void print_thread_created(struct packet_server_s packet, struct client_s *cli)
{
    client_print_thread_created(packet.thread_id, packet.user_id,
        packet.time_stamp, packet.name, packet.body);
    (void)cli;
}