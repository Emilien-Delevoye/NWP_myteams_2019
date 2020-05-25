/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void error_unk_user(struct packet_server_s packet, struct client_s *cli)
{
    client_error_unknown_user(packet.user_id);
    (void)cli;
}