/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void print_team(struct packet_server_s packet, struct client_s *cli)
{
    client_print_team(packet.team_id, packet.name, packet.description);
    (void)cli;
}