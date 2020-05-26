/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void print_user(struct packet_server_s packet, struct client_s *cli)
{
    client_print_user(packet.user_id, packet.name, packet.user_status);
    (void)cli;
}