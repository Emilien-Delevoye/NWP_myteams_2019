/*
** EPITECH PROJECT, 2020
** myteams
** File description:
** Created by emilien
*/

#include "client.h"

void event_th_mes_rx(struct packet_server_s packet, struct client_s *cli)
{
    client_event_thread_message_received(packet.team_id, packet.thread_id,
        packet.user_id, packet.body);
    (void)cli;
}