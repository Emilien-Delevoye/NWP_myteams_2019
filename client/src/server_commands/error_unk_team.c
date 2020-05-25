/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void error_unk_team(struct packet_server_s packet, struct client_s *cli)
{
    client_error_unknown_team(packet.team_id);
    (void)cli;
}