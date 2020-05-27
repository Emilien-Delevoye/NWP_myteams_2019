/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void pv_msg_print_msg(struct packet_server_s packet, struct client_s *cli)
{
    client_private_message_print_messages(packet.user_id, packet.time_stamp,
        packet.body);
    (void)cli;
}