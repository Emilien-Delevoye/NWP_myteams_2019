/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void error_unk_thread(struct packet_server_s packet, struct client_s *cli)
{
    client_error_unknown_thread(packet.thread_id);
    (void)cli;
}