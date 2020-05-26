/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void print_users(struct packet_server_s packet, struct client_s *cli)
{
    client_print_users(packet.user_id, packet.name, packet.user_status);
    (void)cli;
}