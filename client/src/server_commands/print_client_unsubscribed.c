/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void print_client_unsubscribed(struct packet_server_s packet,
    struct client_s *cli)
{
    client_print_unsubscribed(packet.user_id, packet.team_id);
    (void)cli;
}