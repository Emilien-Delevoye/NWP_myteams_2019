/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void error_already_exist(struct packet_server_s packet, struct client_s *cli)
{
    client_error_already_exist();
    (void)packet;
    (void)cli;
}