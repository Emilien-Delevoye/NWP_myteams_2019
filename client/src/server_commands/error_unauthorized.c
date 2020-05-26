/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void error_unauthorized(struct packet_server_s packet, struct client_s *cli)
{
    client_error_unauthorized();
    (void)packet;
    (void)cli;
}